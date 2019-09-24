#include "lexerlua.h"
#include "syslog.h"
#include "mem_tool.h"
#include "mem.h"

CLexerLua::CLexerLua()
{
	this->InitBasic();
}
CLexerLua::~CLexerLua()
{
	this->Destroy();
}
status_t CLexerLua::InitBasic()
{
	CLexer::InitBasic();
	return OK;
}
status_t CLexerLua::Init()
{
	this->InitBasic();
	CLexer::Init();
	return OK;
}
status_t CLexerLua::Destroy()
{
	CLexer::Destroy();
	this->InitBasic();
	return OK;
}
int CLexerLua::NextToken(CFileBase *out)
{
	ASSERT(out);

	out->SetSize(0);

	if(IsEnd())
		return TOKEN_UNKNOWN;

	char ch = this->Getc();
	out->Putc(ch);

	if(ch == '-')
	{
		return this->ReadLuaComments(out);
	}
	else if(ch =='\"')
	{
		this->ReadQuoteStr(out,'\\','\"');
		return TOKEN_STRING;
	}
	else if(ch == '\'')
	{
		this->ReadQuoteStr(out,'\\','\'');
		return TOKEN_STRING;
	}
	else if(ch=='[')
	{
		return this->ReadLuaString(out);
	}
	else if(IS_DEC_NUMBER(ch))
	{
		this->ReadNumber(out);
		return TOKEN_NUMBER;
	}
	else if(ch == '_' || IS_ALPHA(ch))
	{
		this->ReadWord(out);
		return TOKEN_NORMAL_WORD;
	}
	else if(CFileBase::IsEmptyChar(ch))
	{
		this->ReadEmpty(out);
		return TOKEN_EMPTY;
	}
	else
	{
		return TOKEN_PUNCTUATION;
	}

	return TOKEN_UNKNOWN;
}

status_t CLexerLua::ReadLuaComments(CFileBase *out)
{
	ASSERT(out);
	char ch = this->Getc();
	out->Putc(ch);
	
	if(ch == '-')
	{
		ch = this->Getc();
		out->Putc(ch);

		if(ch == '[')
		{
			ch = this->Getc();
			out->Putc(ch);
			if(ch == '[')
			{
				while(!IsEnd())
				{
					ch = this->Getc();					
					out->Putc(ch);
					if(ch == ']')
					{
						ch=this->Getc();
						out->Putc(ch);
						if(ch == ']')
						{
							return TOKEN_MULTI_LINE_COMMENTS;
						}
					}
				}
			}
		}
		else
		{
			while(!IsEnd())
			{
				ch = this->Getc();
				out->Putc(ch);
				if(ch == '\n')
					break;
			}
			return TOKEN_SINGLE_LINE_COMMENTS;
		}	
	}
	else
	{
		out->DeleteLast(1);
		this->UnGetc();
		return TOKEN_PUNCTUATION;
	}
	
	return TOKEN_UNKNOWN;
}

status_t CLexerLua::ReadLuaString(CFileBase *out)
{
	char ch;
	ch = this->Getc();
	out->Putc(ch);
	
	if(ch == '[')
	{
		while(!IsEnd())
		{
			ch = this->Getc();
			out->Putc(ch);
			if(ch == ']')
			{
				ch = this->Getc();
				out->Putc(ch);
				if(ch == ']')
					return TOKEN_STRING;
			}				
		}
	}
	else
	{
		out->DeleteLast(1);
		this->UnGetc();
		return TOKEN_PUNCTUATION;
	}
	return TOKEN_UNKNOWN;
}

#include "lexercpp.h"
#include "syslog.h"
#include "mem_tool.h"
#include "mem.h"

CLexerCpp::CLexerCpp()
{
	this->InitBasic();
}
CLexerCpp::~CLexerCpp()
{
	this->Destroy();
}
status_t CLexerCpp::InitBasic()
{
	is_in_preprocess = false;
	CLexer::InitBasic();
	return OK;
}
status_t CLexerCpp::Init()
{
	this->InitBasic();
	CLexer::Init();
	return OK;
}
status_t CLexerCpp::Destroy()
{
	CLexer::Destroy();
	this->InitBasic();
	return OK;
}
int CLexerCpp::NextToken(CFileBase *out)
{
	ASSERT(out);

	out->SetSize(0);

	if(IsEnd())
		return TOKEN_UNKNOWN;

	char ch = this->Getc();
	out->Putc(ch);

	if(ch == '/')
	{
		return ReadCStyleComments(out);
	}

	if(is_in_preprocess)
	{
		this->ReadPreProcess(out);
		return TOKEN_PREPROCESS;
	}

	if(ch == '#')
	{	
		this->ReadPreProcess(out);
		return TOKEN_PREPROCESS;
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

status_t CLexerCpp::ReadPreProcess(CFileBase *out)
{
	LOCAL_MEM(dummy);
	bool eat_next_line_end = false;

	while(!IsEnd())
	{
		LexContext old_context;
		this->SaveContext(&old_context);

		char ch = this->Getc();

		if(ch == '/')
		{
			int type = ReadCStyleComments(&dummy);
			
			if(type == TOKEN_SINGLE_LINE_COMMENTS || type == TOKEN_MULTI_LINE_COMMENTS)
			{
				is_in_preprocess = true;
				this->RestoreContext(&old_context);
				break;
			}
		}
		
		out->Putc(ch);

		if(ch == '\\')
		{
			eat_next_line_end = true;		
		}
		else if(ch == '\n')
		{
			if(!eat_next_line_end)
			{
				is_in_preprocess = false;
				break;
			}
			eat_next_line_end = false;
		}
		else if(ch != '\r')
		{
			eat_next_line_end = false;
		}
	}
	
	return OK;	
}

status_t CLexerCpp::EatToken(const char *token, bool skip_empty)
{
	ASSERT(token);
	
	LOCAL_MEM(mem);

	LexContext ctx0;
	this->SaveContext(&ctx0);

	if(skip_empty)
	{
		this->SkipEmpty(NULL);
	}

	this->NextToken(&mem);
	if(mem.StrCmp(token) == 0)
		return OK;

	this->RestoreContext(&ctx0);
	return ERROR;
}


status_t CLexerCpp::SkipEmpty(CFileBase *out)
{
	LOCAL_MEM(mem);
	while(!IsEnd())
	{
		LexContext ctx;
		this->SaveContext(&ctx);
		int type = this->NextToken(&mem);
		if(type != TOKEN_EMPTY)
		{
			this->RestoreContext(&ctx);
			return OK;
		}
		if(out)out->Puts(&mem);
	}
	return OK;
}

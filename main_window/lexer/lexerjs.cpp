#include "lexerjs.h"
#include "syslog.h"
#include "mem_tool.h"
#include "mem.h"

CLexerJs::CLexerJs()
{
	this->InitBasic();
}
CLexerJs::~CLexerJs()
{
	this->Destroy();
}
status_t CLexerJs::InitBasic()
{
	CLexer::InitBasic();
	return OK;
}
status_t CLexerJs::Init()
{
	this->InitBasic();
	CLexer::Init();
	return OK;
}
status_t CLexerJs::Destroy()
{
	CLexer::Destroy();
	this->InitBasic();
	return OK;
}
int CLexerJs::NextToken(CFileBase *out)
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

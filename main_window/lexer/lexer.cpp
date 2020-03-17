#include "lexer.h"
#include "syslog.h"
#include "mem_tool.h"

CLexer::CLexer()
{
	this->InitBasic();
}
CLexer::~CLexer()
{
	this->Destroy();
}
status_t CLexer::InitBasic()
{
	WEAK_REF_CLEAR();
	i_SrcFile = NULL;
	m_TmpFile.InitBasic();
	m_CurLine = 0;
	i_KeyWords = NULL;
	m_FuncIsUserKeyWord = NULL;
    m_LastChar = 0;
	return OK;
}
status_t CLexer::Init()
{
	this->InitBasic();
	
	return OK;
}
status_t CLexer::Destroy()
{
    WEAK_REF_DESTROY();
	m_TmpFile.Destroy();
	this->InitBasic();
	return OK;
}
char CLexer::Getc()
{
	ASSERT(i_SrcFile);
	char ch = i_SrcFile->Getc();
	if(ch == '\n')
	{
		m_CurLine ++;
	}
    m_LastChar = ch;
	return ch;
}
char CLexer::UnGetc()
{
	ASSERT(i_SrcFile);
	char ch = i_SrcFile->UnGetc();
	if(ch == '\n')m_CurLine --;
	return ch;
}

status_t CLexer::LoadFile(const char *filename)
{
	m_TmpFile.Destroy();
	m_TmpFile.Init();
	ASSERT(m_TmpFile.LoadFile(filename));
	i_SrcFile = &m_TmpFile;
	m_CurLine = 0;
	return OK;
}

status_t CLexer::LoadFile(CFileBase *file)
{
	ASSERT(file);
	file->Seek(0);
	i_SrcFile = file;
	m_CurLine = 0;
	return OK;
}

status_t CLexer::SetKeyWordTable(const KeyWord *table)
{
	i_KeyWords = (KeyWord*)table;
	return OK;
}

int CLexer::IsKeyWord(CFileBase *name)
{
	ASSERT(name && i_KeyWords);
	int i = 0;
	while(i_KeyWords[i].name)
	{
		if(name->StrCmp(i_KeyWords[i].name) == 0)
			return i_KeyWords[i].type;
		i++;
	}
	return -1;
}
int CLexer::CurrentState()
{
	return m_CurState;
}
status_t CLexer::SetCurrentState(int state)
{
	m_CurState = state;
	return OK;
}

int CLexer::GetCurrentLine()
{
	return m_CurLine;
}

bool CLexer::IsEnd()
{
	ASSERT(i_SrcFile);
	return i_SrcFile->IsEnd();
}


int CLexer::ReadCStyleComments(CFileBase *out)
{
	ASSERT(out);
	char ch = this->Getc();
	out->Putc(ch);

	if(ch == '*')
	{
		bool last_is_star = false;
		while(!IsEnd())
		{
			ch = this->Getc();
			out->Putc(ch);
			if(last_is_star && ch == '/')
			{
				return TOKEN_MULTI_LINE_COMMENTS;
			}
			last_is_star = (ch=='*');		
		}
	}
	else if(ch == '/')
	{
		while(!IsEnd())
		{
			ch = this->Getc();
			out->Putc(ch);				
			if(ch == '\n')
			{
				break;
			}
		}
		return TOKEN_SINGLE_LINE_COMMENTS;
	}
	else
	{
		out->DeleteLast(1);
		this->UnGetc();
		return TOKEN_PUNCTUATION;
	}

	return TOKEN_UNKNOWN;
}
status_t CLexer::ReadQuoteStr(CFileBase *file,char escape_char,char end_char)
{
	ASSERT(file);

	char ch;

	while(!this->IsEnd())
	{
		ch = this->Getc();
		file->Putc(ch);
		if(ch == escape_char)
		{
			ch = this->Getc();
			file->Putc(ch);
		}
		else if(ch == end_char)
		{
			break;
		}		
	}
	return OK;
}

status_t CLexer::ReadNumber(CFileBase *out)
{
	ASSERT(out);
	
	char ch;

	while(!IsEnd())
	{
		ch = this->Getc();
		if(IS_DEC_NUMBER(ch)||IS_ALPHA(ch)||ch=='.')
		{
			out->Putc(ch);
		}
		else
		{
			this->UnGetc();
			break;
		}
	}

	return OK;
}

status_t CLexer::SaveContext(LexContext *context)
{
	ASSERT(context && i_SrcFile);
	context->file_pos = i_SrcFile->GetOffset();
	context->line_number = m_CurLine;
	return OK;
}

status_t CLexer::RestoreContext(LexContext *context)
{
	ASSERT(context && i_SrcFile);
	i_SrcFile->Seek(context->file_pos);
	m_CurLine = context->line_number;
	return OK;
}

status_t CLexer::ReadEmpty(CFileBase *out)
{
	ASSERT(out&&i_SrcFile);

	char ch;
	while(!IsEnd())
	{
		ch = this->Getc();
		if(CFileBase::IsEmptyChar(ch))
		{
			out->Putc(ch);
		}
		else
		{
			this->UnGetc();
			break;
		}
	}

	return OK;
}

status_t CLexer::ReadWord(CFileBase *out)
{
	ASSERT(out&&i_SrcFile);
	
	char ch;
	while(!IsEnd())
	{
		ch = this->Getc();
		if(IS_ALPHA(ch)||IS_DEC_NUMBER(ch)||ch=='_')
		{
			out->Putc(ch);
		}
		else
		{
			this->UnGetc();
			break;
		}
	}	
	return OK;
}

int CLexer::IsUserKeyWord(CFileBase *name)
{
	if(m_FuncIsUserKeyWord)
	{
		return m_FuncIsUserKeyWord(name);
	}
	return -1;
}

status_t CLexer::SetUserKeyWordFunc(FUNC_IS_USER_KEY_WORD func)
{
	m_FuncIsUserKeyWord = func;
	return OK;
}

status_t CLexer::Reset()
{
	ASSERT(i_SrcFile);
	i_SrcFile->Seek(0);
	m_CurLine = 0;
	return OK;
}

bool CLexer::IsUpper(CFileBase *name)
{
	bool has_alpha = false;
	name->Seek(0);
	while(!name->IsEnd())
	{
		char ch = name->Getc();
		if(ch >='a' && ch <='z')
			return false;
		if(ch >= 'A' && ch <='Z')
			has_alpha = true;
	}
	return has_alpha;
}

status_t CLexer::ReportError()
{
	LOG("parse error at line %d",this->GetCurrentLine());
	return OK;
}

#include "idllexer.h"
#include "syslog.h"
#include "mem_tool.h"

#define IS_WHITE(ch) CFileBase::IsEmptyChar(ch)
#define IS_SPLITOR(ch) (ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'||ch==','||ch==';'||ch=='*'||ch=='>'||ch=='<'||ch=='=' || ch==':')
#define IS_NUMBER(ch) (ch>='0'&&ch<='9')
#define IS_ALPHA(ch)  ((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
//#define IS_ALLOW_IN_WORD(ch) (ch=='_'||ch=='@'||ch=='~'||ch=='-'||ch=='.')
#define IS_ALLOW_IN_WORD(ch) ((!IS_SPLITOR(ch))&&(!IS_WHITE(ch)))

CIdlLexer::CIdlLexer()
{
	this->InitBasic();
}
CIdlLexer::~CIdlLexer()
{
	this->Destroy();
}
status_t CIdlLexer::InitBasic()
{
	this->m_Source.InitBasic();
	this->m_CurVal.InitBasic();	
	m_ErrorNo = ERR_NONE;
	return OK;
}
status_t CIdlLexer::Init()
{
	this->InitBasic();
	this->m_Source.Init();
	this->m_CurVal.Init();
	m_CurVal.Malloc(32*1024);
	return OK;
}
status_t CIdlLexer::Destroy()
{
	this->m_Source.Destroy();
	this->m_CurVal.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlLexer::Comp(CIdlLexer *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlLexer::Copy(CIdlLexer *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Source.Copy(&_p->m_Source);
	this->m_CurVal.Copy(&_p->m_CurVal);	
	m_ErrorNo = _p->m_ErrorNo;
	return OK;
}
status_t CIdlLexer::Print(CFileBase *_buf)
{
	const char* _str_source = "<null>";
	if(this->m_Source.StrLen() > 0)
		_str_source = m_Source.CStr();
	_buf->Log("Source = %s",_str_source);
	const char* _str_curval = "<null>";
	if(this->m_CurVal.StrLen() > 0)
		_str_curval = m_CurVal.CStr();
	_buf->Log("CurVal = %s",_str_curval);
	_buf->Log("ErrorNo = %d",m_ErrorNo);
	return OK;
}
CMem* CIdlLexer::GetSource()
{
	return &this->m_Source;
}
CMem* CIdlLexer::GetCurVal()
{
	return &this->m_CurVal;
}
const char* CIdlLexer::GetSourceStr()
{
	return this->m_Source.CStr();
}
const char* CIdlLexer::GetCurValStr()
{
	return this->m_CurVal.CStr();
}
status_t CIdlLexer::SetSource(CMem* _source)
{
	this->m_Source.Copy(_source);
	return OK;
}
status_t CIdlLexer::SetSource(const char *_source)
{
	CMem _mem(_source);
	return this->SetSource(&_mem);
}

status_t CIdlLexer::GetPosAtOffset(fsize_t offset, int *line, int *col)
{
	ASSERT(line && col);
	
	fsize_t old_off = this->GetCurPos();
	
	this->m_Source.Seek(0);
	*line = 1; *col = 1;
	while(!this->m_Source.IsEnd())
	{
		char ch = this->m_Source.Getc();
		
		if(ch == '\n')
		{
			(*line)++;
			(*col) = 1;
		}
		else if(ch == '\t')
			(*col)+=4;
		else
			(*col)++;
		
		if(this->m_Source.GetOffset() >= offset)
			break;
	}
	
	this->m_Source.Seek(old_off);
	return OK;
}

fsize_t CIdlLexer::GetCurPos()
{
	return m_Source.GetOffset();
}

status_t CIdlLexer::LoadSource(const char *filename)
{
	ASSERT(filename);
	m_Source.Destroy();
	m_Source.Init();
	status_t ret = m_Source.LoadFile(filename);
    this->Reset();
    return ret;
}

status_t CIdlLexer::LoadSource(CFileBase *file)
{
    ASSERT(file);
    m_Source.Copy(file);
    this->Reset();
    return OK;
}


status_t CIdlLexer::SaveContext(IdlLexerContext *context)
{
	ASSERT(context);
	context->cur_pos = GetCurPos();
	return OK;
}

status_t CIdlLexer::RestoreContext(IdlLexerContext *context)
{
	ASSERT(context);
	m_Source.Seek(context->cur_pos);
	return OK;
}
status_t CIdlLexer::SetCurVal(CMem* _curval)
{
	this->m_CurVal.Copy(_curval);
	return OK;
}
status_t CIdlLexer::SetCurVal(const char *_curval)
{
	CMem _mem(_curval);
	return this->SetCurVal(&_mem);
}
const char * CIdlLexer::ErrorToString(int err)
{
	switch(err)
	{
		case ERR_INVALID_NUM :
			return "invalidate number string";
		case ERR_INVALID_WORD:
			return "invalidate char sequence in a word";
		case ERR_REACH_END:
			return "unexpected end";
		case ERR_INVALID_CHAR:
			return "invalidate char";
        case ERR_PARSE_ERROR:
            return "syntax error";
	}	
	return "parse error";
}

#define END_LEXIC(err) do{\
	llv = IDL_TOKEN_ERROR;\
	m_ErrorNo = err;\
	goto end;\
}while(0)\

#define RETURN_TOKEN(token) do{\
	llv = token;\
	goto end;\
}while(0)\

#define SINGLE_SYMBOLIC(s,ret) \
if(ch ==s)\
{ \
	this->m_CurVal.Putc(ch);\
	llv = ret; \
	goto end;\
} \

int CIdlLexer::NextTokenAll()
{	
	char ch;
	int llv = IDL_TOKEN_ERROR;
	IdlLexerContext context;

    if(m_ErrorNo != ERR_NONE)
    {
        END_LEXIC(m_ErrorNo);
    }

	if(m_Source.IsEnd())
	{
		END_LEXIC(ERR_REACH_END);		
	}
    
    m_CurVal.SetSize(0);	
	ch = m_Source.Getc();
	////////////////////////////////////////
	if(IS_WHITE(ch))
	{
		m_CurVal.Putc(ch);
		while(!m_Source.IsEnd())
		{
			SaveContext(&context);
			ch = m_Source.Getc();
			if(IS_WHITE(ch))
			{
				m_CurVal.Putc(ch);
			}
			else
			{
				RestoreContext(&context);
				break;
			}
		}
		RETURN_TOKEN(IDL_TOKEN_EMPTY);
	}
	
	////////////////////////////////////////
	if(ch == '/')
	{
		ch = m_Source.Getc();
		if(ch == '/')
		{
			while(!m_Source.IsEnd())
			{
				ch = m_Source.Getc();
				if(ch == '\n')break;
				m_CurVal.Putc(ch);
			}
			RETURN_TOKEN(IDL_TOKEN_COMMENTS);
		}
		else
		{
			END_LEXIC(ERR_INVALID_CHAR);
		}
	}
	/////////////////////////////////////////
    if(ch == '"')
    {
        m_CurVal.Putc(ch);
        LOCAL_MEM(tmp);
        m_Source.ReadCStr(&tmp);
        m_CurVal.Puts(&tmp);
        m_CurVal.Putc(ch);
        RETURN_TOKEN(IDL_TOKEN_STRING);
    }
    /////////////////////////////////////////
	if(IS_ALPHA(ch)||IS_ALLOW_IN_WORD(ch))
	{
		m_CurVal.Putc(ch);
		while(!m_Source.IsEnd())
		{
			SaveContext(&context);
			ch = m_Source.Getc();
			
			if(IS_ALPHA(ch)||IS_ALLOW_IN_WORD(ch)||IS_NUMBER(ch))
			{
				m_CurVal.Putc(ch);
			}
			else if(IS_WHITE(ch) || IS_SPLITOR(ch))
			{
				RestoreContext(&context);
				break;
			}
			else
			{
				END_LEXIC(ERR_INVALID_CHAR);
			}
		}
		RETURN_TOKEN(IDL_TOKEN_WORD);
	}
	/////////////////////////////////////////
	if(IS_NUMBER(ch))
	{
		m_CurVal.Putc(ch);
		while(!m_Source.IsEnd())
		{
			SaveContext(&context);
			ch = m_Source.Getc();
			
			if(IS_NUMBER(ch)||ch=='.'||ch=='x'||ch=='X')
			{
				m_CurVal.Putc(ch);
			}
			else if(IS_WHITE(ch) || IS_SPLITOR(ch))
			{
				RestoreContext(&context);
				break;
			}
			else
			{
				END_LEXIC(ERR_INVALID_NUM);
			}
		}	
		RETURN_TOKEN(IDL_TOKEN_NUMBER);
	}
	///////////////////////////////////////
	SINGLE_SYMBOLIC(',',IDL_TOKEN_COMMA);
	SINGLE_SYMBOLIC(':',IDL_TOKEN_COLON);
	SINGLE_SYMBOLIC('{',IDL_TOKEN_LEFT_BRACE);
	SINGLE_SYMBOLIC('}',IDL_TOKEN_RIGHT_BRACE);
	SINGLE_SYMBOLIC('(',IDL_TOKEN_LEFT_PARENTHESIS);
	SINGLE_SYMBOLIC(')',IDL_TOKEN_RIGHT_PARENTHESIS);
	SINGLE_SYMBOLIC('[',IDL_TOKEN_LEFT_SQUARE_BRACKETS);
	SINGLE_SYMBOLIC(']',IDL_TOKEN_RIGHT_SQUARE_BRACKETS);
	SINGLE_SYMBOLIC('?',IDL_TOKEN_QUESTION_MARK);
	SINGLE_SYMBOLIC(';',IDL_TOKEN_SEMICOLON);
	SINGLE_SYMBOLIC('*',IDL_TOKEN_STAR);
	SINGLE_SYMBOLIC('<',IDL_TOKEN_LESS_THAN);
	SINGLE_SYMBOLIC('>',IDL_TOKEN_GREATER_THAN);
	SINGLE_SYMBOLIC('=',IDL_TOKEN_EQUAL);
	///////////////////////////////////////
    m_CurVal.Putc(ch);
	END_LEXIC(ERR_INVALID_CHAR);
	///////////////////////////////////////
end:
	return llv;
}

status_t CIdlLexer::Reset()
{
	m_Source.Seek(0);
	return OK;
}

int CIdlLexer::GetErrorNo()
{
	return m_ErrorNo;
}

status_t CIdlLexer::Next()
{
    int ret = IDL_TOKEN_ERROR;

    while(true)
    {
        ret = this->NextTokenAll();
        if( ret == IDL_TOKEN_ERROR)
        {
            break;
        }
        
        if( ret != IDL_TOKEN_EMPTY && ret != IDL_TOKEN_COMMENTS)        
        {
            break;
        }
    }
    return ret;
}
bool CIdlLexer::CurValueIs(const char *str)
{
    ASSERT(str);
    return m_CurVal.StrCmp(str) == 0;
}

bool CIdlLexer::IsEnd()
{
    return m_ErrorNo == ERR_REACH_END;
}

status_t CIdlLexer::HasError()
{
    return m_ErrorNo != ERR_NONE && m_ErrorNo != ERR_REACH_END;
}

status_t CIdlLexer::ReportError(CFileBase *buf)
{
    int line = 0,col = 0;
    this->GetPosAtOffset(m_Source.GetOffset(),&line,&col);
    buf->Log("lexical error at line %d,col %d:%s",line,col,ErrorToString(m_ErrorNo));
    return OK;
}

status_t CIdlLexer::GetRawSource(fsize_t start_pos,fsize_t end_pos,CMem *raw)
{
    ASSERT(raw);
    
    raw->Destroy();
    raw->Init();

    if(end_pos > m_Source.GetSize())
        end_pos = m_Source.GetSize();

    if(m_Source.GetSize() <= 0)
        return ERROR;

    fsize_t size = end_pos - start_pos;
    if(size < 0)size = 0;

    if(size <= 0)
        return ERROR;

    raw->SetRawBuf(m_Source.GetRawBuf()+start_pos,(int_ptr_t)size,true);
    return OK;
}


#ifndef __S2_IDLLEXER_H
#define __S2_IDLLEXER_H

#include "cruntime.h"
#include "filebase.h"
#include "mem.h"

enum{
	IDL_TOKEN_ERROR = 0,
	IDL_TOKEN_EMPTY,
	IDL_TOKEN_COMMENTS,
	IDL_TOKEN_NUMBER,
	IDL_TOKEN_WORD,			
    IDL_TOKEN_STRING,
	IDL_TOKEN_COMMA,				// ,
	IDL_TOKEN_STAR,					// *
	IDL_TOKEN_COLON,				// :
	IDL_TOKEN_LEFT_BRACE,			// {
	IDL_TOKEN_RIGHT_BRACE,			// }
	IDL_TOKEN_LEFT_PARENTHESIS,		// (
	IDL_TOKEN_RIGHT_PARENTHESIS,	// )
	IDL_TOKEN_LEFT_SQUARE_BRACKETS,	// [
	IDL_TOKEN_RIGHT_SQUARE_BRACKETS,// ]
	IDL_TOKEN_QUESTION_MARK,		// ?
	IDL_TOKEN_SEMICOLON,			// ;
	IDL_TOKEN_LESS_THAN,			// <
	IDL_TOKEN_GREATER_THAN,			// >
	IDL_TOKEN_EQUAL					// =
};

enum{
	ERR_NONE = 0,
	ERR_INVALID_NUM,
	ERR_REACH_END,
	ERR_INVALID_WORD,
	ERR_INVALID_CHAR,
    ERR_PARSE_ERROR,
};

typedef struct{
	fsize_t cur_pos;
}IdlLexerContext;

class CIdlLexer{
public:
	CMem m_Source;
	CMem m_CurVal;
	int m_ErrorNo;
public:
	status_t GetRawSource(fsize_t start_pos, fsize_t end_pos, CMem *raw);
	status_t ReportError(CFileBase *buf);
	status_t HasError();
	bool IsEnd();
	bool CurValueIs(const char *str);
	int GetErrorNo();
	status_t Reset();
	int NextTokenAll();
    int Next();
	status_t RestoreContext(IdlLexerContext *context);
	status_t SaveContext(IdlLexerContext *context);
	status_t LoadSource(const char *filename);
    status_t LoadSource(CFileBase *file);
	fsize_t GetCurPos();
	CIdlLexer();
	virtual ~CIdlLexer();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlLexer *_p);
	int Comp(CIdlLexer *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetSource();
	CMem* GetCurVal();
	status_t SetSource(CMem* _source);
	status_t SetCurVal(CMem* _curval);
	const char* GetSourceStr();
	const char* GetCurValStr();
	status_t SetSource(const char *_source);
	status_t GetPosAtOffset(fsize_t offset, int *line, int *col);
	status_t SetCurVal(const char *_curval);
	const char * ErrorToString(int err);
};

#endif

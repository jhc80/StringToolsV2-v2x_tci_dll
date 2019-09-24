#ifndef __S2_LEXERCPP_H
#define __S2_LEXERCPP_H

#include "cruntime.h"
#include "filebase.h"
#include "lexer.h"

class CLexerCpp:public CLexer{
public:
	bool is_in_preprocess;
public:
	status_t SkipEmpty(CFileBase *out);
	status_t EatToken(const char *token, bool skip_empty);
	status_t ReadPreProcess(CFileBase *out);
	int NextToken(CFileBase *out);
	CLexerCpp();
	virtual ~CLexerCpp();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
};

#endif

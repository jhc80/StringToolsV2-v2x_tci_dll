#ifndef __S2_LEXERLUA_H
#define __S2_LEXERLUA_H

#include "cruntime.h"
#include "filebase.h"
#include "lexer.h"

class CLexerLua:public CLexer{
public:
public:
	status_t ReadLuaString(CFileBase *out);
	status_t ReadLuaComments(CFileBase *out);
	int NextToken(CFileBase *out);
	CLexerLua();
	virtual ~CLexerLua();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
};

#endif

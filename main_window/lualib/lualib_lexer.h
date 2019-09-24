#ifndef __LUALIB_LEXER_H
#define __LUALIB_LEXER_H

#include "lexer.h"
#include "filebase.h"
#include "luavm.h"

#define LUA_USERDATA_LEXER "lua_userdata_lexer"

CLexer* get_lexer(lua_State *L, int idx);
lua_userdata *lexer_new_userdata(lua_State *L,CLexer *pobj,int is_weak);
int luaopen_lexer(lua_State *L);
bool is_lexer(lua_State *L, int idx);
const luaL_Reg* get_lexer_funcs();


#endif

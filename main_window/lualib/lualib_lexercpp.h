#ifndef __LUALIB_LEXERCPP_H
#define __LUALIB_LEXERCPP_H

#include "lexercpp.h"
#include "filebase.h"
#include "lexer.h"
#include "luavm.h"

#define LUA_USERDATA_LEXERCPP "lua_userdata_lexercpp"

CLexerCpp* get_lexercpp(lua_State *L, int idx);
lua_userdata *lexercpp_new_userdata(lua_State *L,CLexerCpp *pobj,int is_weak);
int luaopen_lexercpp(lua_State *L);
bool is_lexercpp(lua_State *L, int idx);
const luaL_Reg* get_lexercpp_funcs();

#endif

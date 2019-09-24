#ifndef __LUALIB_LEXERLUA_H
#define __LUALIB_LEXERLUA_H

#include "lexerlua.h"
#include "filebase.h"
#include "lexer.h"
#include "luavm.h"

#define LUA_USERDATA_LEXERLUA "lua_userdata_lexerlua"

CLexerLua* get_lexerlua(lua_State *L, int idx);
lua_userdata *lexerlua_new_userdata(lua_State *L,CLexerLua *pobj,int is_weak);
int luaopen_lexerlua(lua_State *L);
bool is_lexerlua(lua_State *L, int idx);
const luaL_Reg* get_lexerlua_funcs();


#endif

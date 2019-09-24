#ifndef __LUALIB_IDLPARSER_H
#define __LUALIB_IDLPARSER_H

#include "idlparser.h"
#include "filebase.h"
#include "luavm.h"

#define LUA_USERDATA_IDLPARSER "lua_userdata_idlparser"

CIdlParser *get_idlparser(lua_State *L, int idx);
lua_userdata *idlparser_new_userdata(lua_State *L,CIdlParser *pt,int is_weak);
int luaopen_idlparser(lua_State *L);
bool is_idlparser(lua_State *L, int idx);

#endif

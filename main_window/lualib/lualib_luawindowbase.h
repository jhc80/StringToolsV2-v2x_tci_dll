#ifndef __LUALIB_LUAWINDOWBASE_H
#define __LUALIB_LUAWINDOWBASE_H

#include "lua_window_base.h"
#include "luavm.h"

#define LUA_USERDATA_LUAWINDOWBASE "lua_userdata_luawindowbase"

CLuaWindowBase* get_luawindowbase(lua_State *L, int idx);
lua_userdata *luawindowbase_new_userdata(lua_State *L,CLuaWindowBase *pobj,int is_weak);
int luaopen_luawindowbase(lua_State *L);
bool is_luawindowbase(lua_State *L, int idx);
const luaL_Reg* get_luawindowbase_funcs();

#endif

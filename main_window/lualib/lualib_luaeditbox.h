#ifndef __LUALIB_LUAEDITBOX_H
#define __LUALIB_LUAEDITBOX_H

#include "lua_edit_box.h"
#include "luavm.h"

#define LUA_USERDATA_LUAEDITBOX "lua_userdata_luaeditbox"

CLuaEditBox* get_luaeditbox(lua_State *L, int idx);
lua_userdata *luaeditbox_new_userdata(lua_State *L,CLuaEditBox *pobj,int is_weak);
int luaopen_luaeditbox(lua_State *L);
bool is_luaeditbox(lua_State *L, int idx);
const luaL_Reg* get_luaeditbox_funcs();

#endif

#ifndef __LUALIB_LUABUTTON_H
#define __LUALIB_LUABUTTON_H

#include "lua_button.h"
#include "luavm.h"

#define LUA_USERDATA_LUABUTTON "lua_userdata_luabutton"

CLuaButton* get_luabutton(lua_State *L, int idx);
lua_userdata *luabutton_new_userdata(lua_State *L,CLuaButton *pobj,int is_weak);
int luaopen_luabutton(lua_State *L);
bool is_luabutton(lua_State *L, int idx);
const luaL_Reg* get_luabutton_funcs();

#endif

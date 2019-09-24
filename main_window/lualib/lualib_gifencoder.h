#ifndef __LUALIB_GIFENCODER_H
#define __LUALIB_GIFENCODER_H

#include "gif_encoder.h"
#include "luavm.h"

#define LUA_USERDATA_GIFENCODER "lua_userdata_gifencoder"

CGifEncoder* get_gifencoder(lua_State *L, int idx);
lua_userdata *gifencoder_new_userdata(lua_State *L,CGifEncoder *pobj,int is_weak);
int luaopen_gifencoder(lua_State *L);
bool is_gifencoder(lua_State *L, int idx);
const luaL_Reg* get_gifencoder_funcs();

#endif

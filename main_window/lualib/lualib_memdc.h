#ifndef __LUALIB_MEMDC_H
#define __LUALIB_MEMDC_H

#include "memdc.h"
#include "luavm.h"

#define LUA_USERDATA_MEMDC "lua_userdata_memdc"

CMemDC* get_memdc(lua_State *L, int idx);
lua_userdata *memdc_new_userdata(lua_State *L,CMemDC *pobj,int is_weak);
int luaopen_memdc(lua_State *L);
bool is_memdc(lua_State *L, int idx);
const luaL_Reg* get_memdc_funcs();

#endif

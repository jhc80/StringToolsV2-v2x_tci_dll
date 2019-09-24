#ifndef __LUALIB_SCREEN_H
#define __LUALIB_SCREEN_H

#include "ximage.h"
#include "luavm.h"

#define LUA_USERDATA_SCREEN "lua_userdata_screen"

int luaopen_screen(lua_State *L);

#endif

#ifndef __LUALIB_APP_H
#define __LUALIB_APP_H

#include "luavm.h"
#include "mem.h"

#define LUA_USERDATA_APP "lua_userdata_app"

int luaopen_app(lua_State *L);
status_t app_callback_onappevent(lua_State *L, int _funcid, bool _once, int event, CMem *mem);

#endif

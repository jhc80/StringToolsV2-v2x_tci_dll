#ifndef __LUA_HELPER_H
#define __LUA_HELPER_H

#include "luavm.h"

const char* lua_push_local_string(lua_State *L, const char *local_string);
const char* lua_to_local_string(lua_State *L, int index);

#endif

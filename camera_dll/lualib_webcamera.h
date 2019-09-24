#ifndef __LUALIB_WEBCAMERA_H
#define __LUALIB_WEBCAMERA_H

#include "webcamera.h"
#include "luavm.h"

#define LUA_USERDATA_WEBCAMERA "lua_userdata_webcamera"

CWebCamera *get_webcamera(lua_State *L, int idx);
lua_userdata *webcamera_new_userdata(lua_State *L,CWebCamera *pt,int is_weak);
DLL_EXPORT_C int luaopen_webcamera(lua_State *L);
bool is_webcamera(lua_State *L, int idx);

#endif

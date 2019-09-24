#ifndef __LOAD_DLL_H
#define __LOAD_DLL_H

#include "cruntime.h"

struct lua_dll_init_data{
    uint32_t this_size;
    uint32_t lua_state_size;
    uint32_t main_hwnd;
    void *log_ptr;
};

#define LUA_INIT_FUNC_NAME "lua_dll_init"

typedef int (*LUA_INIT_FUNC)(struct lua_dll_init_data *init_data);


#endif



#include "dll.h"
#include "mem.h"
#include "luavm.h"
#include "syslog.h"
#include "load_dll.h"

static int dll_add(lua_State *L)
{
    int a = (int)lua_tointeger(L,1);
    int b = (int)lua_tointeger(L,2);
    int _ret_0 = a+b;
    lua_pushinteger(L,_ret_0);
    PD(_ret_0);
    return 1;
}
static const luaL_Reg dll_lib[] = {
    {"add",dll_add},
    {NULL, NULL}
};
static int luaL_register_dll(lua_State *L)
{	
    luaL_newmetatable(L, "dll");
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,dll_lib,0);
    lua_pop(L, 1);
    luaL_newlib(L,dll_lib);
    return 1;
}

DLL_EXPORT_C int luaopen_test(lua_State *L)
{
    luaL_requiref(L, "DLL",luaL_register_dll,1);
    lua_pop(L, 1);
    return 0;
}



DLL_EXPORT_C int lua_dll_init(struct lua_dll_init_data *init_data)
{
    if(init_data->this_size != sizeof(lua_dll_init_data))
    {
        MessageBoxW(0,L"lua_dll_init_data size mismatch.",L"dll error",MB_ICONSTOP);
        return ERROR;
    }

    if(init_data->lua_state_size != (uint32_t)lua_State_Size)
    {
        MessageBoxW(0,L"lua_State size mismatch.",L"dll error",MB_ICONSTOP);
        return ERROR;
    }
    syslog_set_puts_handler((SYSLOG_PUTS_HANDLER)init_data->log_ptr);
    return OK;    
}

BOOL APIENTRY DllMain( HINSTANCE instance, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


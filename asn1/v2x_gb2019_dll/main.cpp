#include "mem.h"
#include "luavm.h"
#include "syslog.h"
#include "load_dll.h"
#include "memfile.h"
#include "encoder.h"

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


#include "mem.h"
#include "luavm.h"
#include "syslog.h"
#include "load_dll.h"
#include "memfile.h"
#include "encoder.h"

extern "C"{
#include "asn1p_to_lua.h"
}

#define LUA_USERDATA_ASN1PARSER "lua_userdata_asn1parser"

static int asn1parser_parsefilelist(lua_State *L)
{
	CMemStk list;
	list.Init(1024);
	CLuaVm::ToStringArray(L,1,&list);

	if(list.GetLen() <= 0)
		return 0;

	const int MAX_FILES = 10000;
	const char *str_array[MAX_FILES];

	ASSERT(list.GetLen() < MAX_FILES);

	for(int i = 0; i < list.GetLen(); i++)
	{
		CEncoder::EncodingConvert(ENCODING_UTF8,LOCAL_ENCODING,list.GetElem(i));
		str_array[i] = list.GetElem(i)->CStr();
	}

	int size = 0;
	
	char *res = asn1_parse_all_files(
		str_array,list.GetLen(),&size
	);

	if(res && size > 0)
	{
		lua_pushlstring(L,res,size);
		free(res);
		return 1;
	}

	return 0;
}

static int asn1parser_parsestring(lua_State *L)
{
	size_t len = 0;
	const char *str = lua_tolstring(L,1,&len);
	if(!str)return 0;

	int lua_len = 0;
	const char *lua = asn1_parse_string(str,len,&lua_len);

	if(!lua)return 0;
	if(lua_len == 0)return 0;

	lua_pushlstring(L,lua,lua_len);	
	return 1;
}

static const luaL_Reg asn1parser_lib[] = {
	{"ParseString",asn1parser_parsestring},
	{"ParseFileList",asn1parser_parsefilelist},
	{NULL, NULL}
};


static int luaL_register_asn1parser(lua_State *L)
{	
	luaL_newmetatable(L, LUA_USERDATA_ASN1PARSER);
	lua_pushvalue(L, -1);	
	lua_setfield(L, -2, "__index");	
	luaL_setfuncs(L,asn1parser_lib,0);
	lua_pop(L, 1);
	luaL_newlib(L,asn1parser_lib);
	return 1;
}


DLL_EXPORT_C int luaopen_asn1parser(lua_State *L)
{
	luaL_requiref(L, "ASN1",luaL_register_asn1parser,1);
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


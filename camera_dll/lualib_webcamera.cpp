#include "lualib_webcamera.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lua_helper.h"
#include "dll.h"

status_t CreateHiddenCameraHostWindow();
status_t DestroyHiddenCameraHostWindow();
CWnd* GetHiddenCameraHostWindow();

LUA_IS_VALID_USER_DATA_FUNC(CWebCamera,webcamera)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CWebCamera,webcamera)
LUA_NEW_USER_DATA_FUNC(CWebCamera,webcamera,WEBCAMERA)
LUA_GC_FUNC(CWebCamera,webcamera)
LUA_IS_SAME_FUNC(CWebCamera,webcamera)
LUA_TO_STRING_FUNC(CWebCamera,webcamera)

bool is_webcamera(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_WEBCAMERA,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return webcamera_is_userdata_valid(ud);  
}
/****************************************/
static int webcamera_new(lua_State *L)
{
    CWebCamera *pt;
    NEW(pt,CWebCamera);
    pt->Init();
    webcamera_new_userdata(L,pt,0);
    return 1;
}

static int webcamera_isvalid(lua_State *L)
{
    CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int _ret_0 = (int)pwebcamera->IsValid();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_setvideowindowvisible(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int v = (int)lua_toboolean(L,2);
	int _ret_0 = (int)pwebcamera->SetVideoWindowVisible(v!=0);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_stop(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int _ret_0 = (int)pwebcamera->Stop();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_getpixelheight(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int _ret_0 = (int)pwebcamera->GetPixelHeight();
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int webcamera_getpixelwidth(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int _ret_0 = (int)pwebcamera->GetPixelWidth();
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int webcamera_takepicturebmp(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int _ret_0 = (int)pwebcamera->TakePictureBmp();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_getframedata(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	
    CMem *data = pwebcamera->GetFrameData();
	ASSERT(data);
	lua_pushinteger(L,(int_ptr_t)data->GetRawBuf());
	lua_pushinteger(L,data->GetSize());
	return 2;
}

static int webcamera_start(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
    
    CreateHiddenCameraHostWindow();
    ASSERT(GetHiddenCameraHostWindow());
    pwebcamera->SetHostWindow(GetHiddenCameraHostWindow()->hwnd);

    int _ret_0 = (int)pwebcamera->Start();
    pwebcamera->SetVideoWindowVisible(false);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_setactivedevice(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);
	int index = (int)lua_tointeger(L,2);
	int _ret_0 = (int)pwebcamera->SetActiveDevice(index);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int webcamera_getalldevicenames(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	ASSERT(pwebcamera);

    CMemFile list;
    list.Init();
    pwebcamera->GetAllDeviceNames(&list);

    lua_newtable(L);
    int top = lua_gettop(L);

    list.Seek(0);

    LOCAL_MEM(mem);
    int i = 1;

    while(list.ReadLine(&mem))
    {
        lua_pushinteger(L,i++);
        lua_push_local_string(L,mem.CStr());
        lua_settable(L, top);
    }

	return 1;
}
static const luaL_Reg webcamera_lib[] = {
    {"__gc",webcamera_gc_},
    {"__tostring",webcamera_tostring_},
    {"__is_same",webcamera_issame_},
    {"new",webcamera_new},
	{"IsValid",webcamera_isvalid},
	{"SetVideoWindowVisible",webcamera_setvideowindowvisible},
	{"Stop",webcamera_stop},
	{"GetPixelHeight",webcamera_getpixelheight},
	{"GetPixelWidth",webcamera_getpixelwidth},
	{"TakePictureBmp",webcamera_takepicturebmp},
	{"GetFrameData",webcamera_getframedata},
	{"Start",webcamera_start},
	{"SetActiveDevice",webcamera_setactivedevice},
	{"GetAllDeviceNames",webcamera_getalldevicenames},
	{NULL, NULL}
};
static int luaL_register_webcamera(lua_State *L)
{	
	luaL_newmetatable(L, LUA_USERDATA_WEBCAMERA);
	lua_pushvalue(L, -1);	
	lua_setfield(L, -2, "__index");	
	luaL_setfuncs(L,webcamera_lib,0);
	lua_pop(L, 1);
	luaL_newlib(L,webcamera_lib);
	return 1;
}

DLL_EXPORT_C int luaopen_webcamera(lua_State *L)
{
	luaL_requiref(L, "WebCamera",luaL_register_webcamera,1);
	lua_pop(L, 1);
	return 0;
}

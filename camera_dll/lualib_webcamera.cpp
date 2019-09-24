#include "lualib_webcamera.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lua_helper.h"
#include "dll.h"

status_t CreateHiddenCameraHostWindow();
status_t DestroyHiddenCameraHostWindow();
CWnd* GetHiddenCameraHostWindow();

static bool webcamera_is_userdata_valid(lua_userdata *ud)
{
	if(ud == NULL)return false;
	if(ud->p == NULL)return false;
	if(ud->__weak_ref_id == 0) return false;
	CWebCamera *p = (CWebCamera*)ud->p;
	return p->__weak_ref_id == ud->__weak_ref_id;
}
bool is_webcamera(lua_State *L, int idx)
{
	lua_userdata *ud = (lua_userdata*)luaL_testudata(L, idx, LUA_USERDATA_WEBCAMERA);
	return webcamera_is_userdata_valid(ud);
}
CWebCamera *get_webcamera(lua_State *L, int idx)
{
	lua_userdata *ud = (lua_userdata*)luaL_checkudata(L, idx, LUA_USERDATA_WEBCAMERA);
	ASSERT(ud && ud->p);
	ASSERT(ud->__weak_ref_id != 0);
	CWebCamera *p = (CWebCamera*)ud->p;
	ASSERT(p->__weak_ref_id == ud->__weak_ref_id);
	return p;
}
lua_userdata *webcamera_new_userdata(lua_State *L,CWebCamera *pt,int is_weak)
{
	lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
	ASSERT(ud && pt);
	ud->p = pt;
	ud->is_attached = is_weak;
	ud->__weak_ref_id = pt->__weak_ref_id;
	luaL_getmetatable(L,LUA_USERDATA_WEBCAMERA);
	lua_setmetatable(L,-2);
	return ud;
}

static int webcamera_new(lua_State *L)
{
	CWebCamera *pt;
	NEW(pt,CWebCamera);
	pt->Init();
	webcamera_new_userdata(L,pt,0);
	return 1;
}

static int webcamera_destroy(lua_State *L)
{
	lua_userdata *ud = (lua_userdata*)luaL_checkudata(L, 1, LUA_USERDATA_WEBCAMERA);
	if(!webcamera_is_userdata_valid(ud))
		return 0;
	CWebCamera *pwebcamera = (CWebCamera*)ud->p;
	if(!(ud->is_attached))
	{
		DEL(pwebcamera);
	}
	return 0;
}
static int webcamera_issame(lua_State *L)
{
	CWebCamera *pwebcamera1 = get_webcamera(L,1);
	ASSERT(pwebcamera1);
	CWebCamera *pwebcamera2 = get_webcamera(L,2);
	ASSERT(pwebcamera2);
	int is_same = (pwebcamera1==pwebcamera2);
	lua_pushboolean(L,is_same);
	return 1;
}
static int webcamera_tostring(lua_State *L)
{
	CWebCamera *pwebcamera = get_webcamera(L,1);
	char buf[1024];
	sprintf(buf,"userdata:webcamera:%p",pwebcamera);
	lua_pushstring(L,buf);
	return 1;
}
/****************************************/
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
	{"new",webcamera_new},
	{"__gc",webcamera_destroy},
	{"__tostring",webcamera_tostring},
	{"IsSame",webcamera_issame},
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

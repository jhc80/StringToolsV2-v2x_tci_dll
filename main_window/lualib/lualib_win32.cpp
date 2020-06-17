#include "lualib_win32.h"
#include "lualib_luahdc.h"
#include "mem_tool.h"
#include "syslog.h"
#include "globals.h"
/****************************************************/
status_t win32_callback_onwindowmessage(lua_State *L, int _funcid, bool _once, uint32_t hwnd, uint32_t msg, uint32_t wparam, uint32_t lparam)
{
    if(_funcid == LUA_REFNIL)
    {
        return ERROR;
    }

    CLuaVm vm;
    vm.Init(L);
    lua_rawgeti(L,LUA_REGISTRYINDEX,_funcid);
    if(_once)
    {
        luaL_unref(L,LUA_REGISTRYINDEX,_funcid);
    }
    lua_pushinteger(L,hwnd);
    lua_pushinteger(L,msg);
    lua_pushinteger(L,wparam);
    lua_pushinteger(L,lparam);
    vm.Run(4,0);
    vm.ClearStack();
    return OK;
}

static status_t win32_setonwindowmessage(lua_State *L)
{
    int on_msg = CLuaVm::ToFunction(L,1);
    GLOBAL_LUA_THREAD(lua_thread);
    CLuaVm::ReleaseFunction(L,lua_thread->callback_on_window_message);
    lua_thread->callback_on_window_message = on_msg;    
    return 0;
}

static status_t win32_getclientrect(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);
    RECT r;
    ::GetClientRect(hwnd,&r);
    lua_pushinteger(L,r.left);
    lua_pushinteger(L,r.top);
    lua_pushinteger(L,r.right);
    lua_pushinteger(L,r.bottom);
    return 4;
}

static status_t win32_getasynckeystate(lua_State *L)
{
    int vk = (int)lua_tointeger(L,1);
    int ret0 = ::GetAsyncKeyState(vk);
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t win32_getcursorpos(lua_State *L)
{
    POINT p;
    GetCursorPos(&p);
    lua_pushinteger(L,p.x);
    lua_pushinteger(L,p.y);
    return 2;
}

static status_t win32_setcursorpos(lua_State *L)
{
    int x = (int)lua_tointeger(L,1);
    int y = (int)lua_tointeger(L,2);
    int ret0 = ::SetCursorPos(x,y);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t win32_getdesktopwindow(lua_State *L)
{
    HWND ret0 = ::GetDesktopWindow();
    lua_pushinteger(L,(lua_Integer)ret0);
    return 1;
}

static status_t win32_getdc(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);  
    
    CLuaHdc *hdc;
    NEW(hdc,CLuaHdc);
    hdc->Init();
    hdc->Set(hwnd,::GetDC(hwnd));

    luahdc_new_userdata(L,hdc,0);
    return 1;
}

static status_t win32_getwindowdc(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);  
    
    CLuaHdc *hdc;
    NEW(hdc,CLuaHdc);
    hdc->Init();
    hdc->Set(hwnd,::GetWindowDC(hwnd));

    luahdc_new_userdata(L,hdc,0);
    return 1;
}

static status_t win32_getpixel(lua_State *L)
{
    CLuaHdc *hdc = get_luahdc(L,1);
    ASSERT(hdc);    
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    uint32_t ret0 = ::GetPixel(hdc->hdc,x,y);
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t win32_sendmessage(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);
    uint32_t message = (uint32_t)lua_tointeger(L,2);
    uint32_t wparam = (uint32_t)lua_tointeger(L,3);
    uint32_t lparam = (uint32_t)lua_tointeger(L,4);
    uint32_t ret0 = ::SendMessageW(hwnd,message,wparam,lparam);
    lua_pushinteger(L,ret0);
    return 1;
}
static status_t win32_bitblt(lua_State *L)
{
    CLuaHdc *hdc = get_luahdc(L,1);
    ASSERT(hdc);
    int x = (int)lua_tointeger(L,2);
    int y = (int)lua_tointeger(L,3);
    int width = (int)lua_tointeger(L,4);
    int height = (int)lua_tointeger(L,5);
    CLuaHdc *hdc_src = get_luahdc(L,6);
    ASSERT(hdc_src);
    int left = (int)lua_tointeger(L,7);
    int top = (int)lua_tointeger(L,8);
    uint32_t op = (uint32_t)lua_tointeger(L,9);
    status_t ret0 = ::BitBlt(hdc->hdc,x,y,width,height,hdc_src->hdc,left,top,op);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t win32_getwindowrect(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);
	
	RECT r;
	::GetWindowRect(hwnd,&r);

	int rr[4];
	rr[0] = r.left;
	rr[1] = r.top;
	rr[2] = r.right;
	rr[3] = r.bottom;

	CLuaVm::PushIntArray(L,rr,4);
	
    return 1;
}

static status_t win32_setfocus(lua_State *L)
{
    HWND hwnd = (HWND)lua_tointeger(L,1);
    ::SetFocus(hwnd);
    return 0;
}

/****************************************************/
static const luaL_Reg win32_funcs_[] = {
    {"SetOnWindowMessage",win32_setonwindowmessage},
    {"GetAsyncKeyState",win32_getasynckeystate},
    {"GetClientRect",win32_getclientrect},
    {"GetCursorPos",win32_getcursorpos},
    {"SetCursorPos",win32_setcursorpos},
    {"GetDesktopWindow",win32_getdesktopwindow},
    {"GetDC",win32_getdc},
	{"GetWindowDC",win32_getdc},
    {"GetPixel",win32_getpixel},	
    {"SendMessage",win32_sendmessage},
    {"BitBlt",win32_bitblt},	
    {"GetWindowRect",win32_getwindowrect},    
    {"SetFocus",win32_setfocus},
    {NULL,NULL},
};

const luaL_Reg* get_win32_funcs()
{
    return win32_funcs_;
}

static int luaL_register_win32(lua_State *L)
{	
    static luaL_Reg _win32_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_win32_funcs_,&_index,get_win32_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_WIN32);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_win32_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_win32_funcs_);
    return 1;
}        

int luaopen_win32(lua_State *L)
{
    luaL_requiref(L, "Win32",luaL_register_win32,1);
    lua_pop(L, 1);
    return 0;
}        


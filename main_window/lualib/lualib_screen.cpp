#include "lualib_screen.h"
#include "lualib_ximage.h"
#include "lualib_filebase.h"
#include "mem_tool.h"
#include "syslog.h"
#include "globals.h"
#include "ximagehelper.h"
#include "lua_helper.h"

static int screen_getwidth(lua_State *L)
{
    GLOBAL_SCREEN_BUFFER(screen);
	int _ret_0 = screen->GetWidth();
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int screen_getheight(lua_State *L)
{
    GLOBAL_SCREEN_BUFFER(screen);
	int _ret_0 = screen->GetHeight();
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int screen_getbackimage(lua_State *L)
{
    GLOBAL_SCREEN_BUFFER(screen);
	CxImage *_ret_0 = screen->GetImageBuffer();
	if(_ret_0==NULL)return 0;
	ximage_new_userdata(L,_ret_0,1);
	return 1;
}
static int screen_redraw(lua_State *L)
{
    BEGIN_NEW_CLOSURE(run)
    {
        GLOBAL_PAGE_IMAGE(page_image);
        page_image->RefreshUI();
        return OK;
    }
    END_NEW_CLOSURE(run);

    GLOBAL_MAIN_TASK_RUNNER(runner);
	runner->AddClosure(run,0);
    return 0;
}
static int screen_resize(lua_State *L)
{
	GLOBAL_SCREEN_BUFFER(screen);
    GLOBAL_PAGE_IMAGE(page_image);
	
	int w = (int)lua_tointeger(L,1);
	int h = (int)lua_tointeger(L,2);
	
	if(w != screen->GetWidth() || h != screen->GetHeight())
	{
		page_image->ResetPosition();
	}

    screen->Lock();    
	int _ret_0 = (int)screen->Resize(w,h);
    screen->Unlock();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int screen_create(lua_State *L)
{
    GLOBAL_SCREEN_BUFFER(screen);
    GLOBAL_PAGE_IMAGE(page_image);
	int w = (int)lua_tointeger(L,1);
	int h = (int)lua_tointeger(L,2);
    page_image->ResetPosition_ThreadSafe();
    screen->Lock();
	int _ret_0 = (int)screen->Create(w,h);    
    screen->Unlock();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int screen_loadimage_v1(lua_State *L)
{
    CFileBase *file = get_filebase(L,1);
    ASSERT(file);
    GLOBAL_SCREEN_BUFFER(screen);
    CxImage *img = screen->GetImageBuffer();
    ASSERT(img);
    screen->Lock();
    CxImageHelper::LoadImage(file,img);
    screen->Unlock();
    return 1;
}
static int screen_loadimage_v2(lua_State *L)
{
	LUA_TO_LOCAL_STRING(filename,L,1);
    GLOBAL_SCREEN_BUFFER(screen);
    CxImage *img = screen->GetImageBuffer();
    ASSERT(img);
    screen->Lock();
    CxImageHelper::LoadImage(filename,img);
    screen->Unlock();
    return 0;
}
static int screen_loadimage(lua_State *L)
{
    if(lua_isstring(L,1))
        return screen_loadimage_v2(L);
    else
        return screen_loadimage_v1(L);
}

static int screen_clear(lua_State *L)
{
    GLOBAL_SCREEN_BUFFER(screen);
    int color = (int)lua_tointeger(L,1);
    int _ret_0 = (int)screen->Clear(color);
    lua_pushboolean(L,_ret_0);
    return 1;
}
static int screen_resample(lua_State *L)
{
    int neww = (int)lua_tointeger(L,1);
    int newh = (int)lua_tointeger(L,2);
    GLOBAL_SCREEN_BUFFER(screen);
    screen->Lock();
    screen->Resample(neww,newh);
    screen->Unlock();
    return 0;
}
static int screen_getviewwidth(lua_State *L)
{
    RECT r;
    GLOBAL_PAGE_IMAGE(page_image);
    ::GetClientRect(page_image->hwnd,&r);
    int _ret_0 = r.right - r.left;
    lua_pushinteger(L,_ret_0);
    return 1;
}
static int screen_getviewheight(lua_State *L)
{
    RECT r;
    GLOBAL_PAGE_IMAGE(page_image);
    ::GetClientRect(page_image->hwnd,&r);
    int _ret_0 = r.bottom-r.top;
    lua_pushinteger(L,_ret_0);
    return 1;
}
static int screen_drawimage(lua_State *L)
{
    CxImage *img = get_ximage(L,1);
    ASSERT(img);
    int offx = (int)lua_tointeger(L,2);
    int offy = (int)lua_tointeger(L,3);
    int op = OpScreen;
    if(lua_isinteger(L,4))
    {
        op = (int)lua_tointeger(L,4);
    }

    bool mix_alpha = false;    
    if(lua_isinteger(L,5))
    {
        mix_alpha = lua_toboolean(L,5)!=0;
    }
    
    GLOBAL_SCREEN_BUFFER(screen);
    screen->DrawImage(img,offx,offy,op,mix_alpha);
    return 0;
}

static status_t screen_refreshui(lua_State *L)
{
    GLOBAL_PAGE_IMAGE(page_image);
	page_image->RefreshUI();
    return 0;
}

static status_t screen_refreshscreen(lua_State *L)
{
    bool clear = lua_toboolean(L,1)!=0;
    GLOBAL_PAGE_IMAGE(page_image);
	page_image->RefreshScreen(clear);
	return 0;
}

static const luaL_Reg screen_lib[] = {
	{"GetWidth",screen_getwidth},
	{"GetHeight",screen_getheight},
	{"GetBackImage",screen_getbackimage},
	{"Redraw",screen_redraw},
	{"Resize",screen_resize},
	{"Create",screen_create},
    {"LoadImage",screen_loadimage},
	{"Clear",screen_clear},    
	{"Resample",screen_resample},
    {"GetViewWidth",screen_getviewwidth},
	{"GetViewHeight",screen_getviewheight},
	{"DrawImage",screen_drawimage},
    {"RefreshUI",screen_refreshui},
    {"RefreshScreen",screen_refreshscreen},
	{NULL, NULL}
};
static int luaL_register_screen(lua_State *L)
{	
	luaL_newmetatable(L, LUA_USERDATA_SCREEN);
	lua_pushvalue(L, -1);	
	lua_setfield(L, -2, "__index");	
	luaL_setfuncs(L,screen_lib,0);
	lua_pop(L, 1);
	luaL_newlib(L,screen_lib);
	return 1;
}

int luaopen_screen(lua_State *L)
{
	luaL_requiref(L, "Screen",luaL_register_screen,1);
	lua_pop(L, 1);
	return 0;
}

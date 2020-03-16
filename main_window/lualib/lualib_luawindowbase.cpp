#include "lualib_luawindowbase.h"
#include "lualib_luabutton.h"
#include "lualib_luaeditbox.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_mem.h"
#include "encoder.h"

static bool luawindowbase_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CHECK_IS_UD_READABLE(CLuaWindowBase,ud);
    CLuaWindowBase *p = (CLuaWindowBase*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_luawindowbase(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LUAWINDOWBASE,
        LUA_USERDATA_LUABUTTON,
        LUA_USERDATA_LUAEDITBOX,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return luawindowbase_is_userdata_valid(ud);  
}

CLuaWindowBase *get_luawindowbase(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_luawindowbase(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CLuaWindowBase *)ud->p;
} 

lua_userdata *luawindowbase_new_userdata(lua_State *L,CLuaWindowBase *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_LUAWINDOWBASE);
    lua_setmetatable(L,-2);
    return ud;
}

static int luawindowbase_gc_(lua_State *L)
{
    if(!is_luawindowbase(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CLuaWindowBase *pluawindowbase = (CLuaWindowBase*)ud->p;
        DEL(pluawindowbase);
    }
    return 0;
}

static int luawindowbase_issame_(lua_State *L)
{
    CLuaWindowBase *pluawindowbase1 = get_luawindowbase(L,1);
    ASSERT(pluawindowbase1);
    CLuaWindowBase *pluawindowbase2 = get_luawindowbase(L,2);
    ASSERT(pluawindowbase2);
    int is_same = (pluawindowbase1==pluawindowbase2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int luawindowbase_tostring_(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    char buf[1024];
    sprintf(buf,"userdata:luawindowbase:%p",pluawindowbase);
    lua_pushstring(L,buf);
    return 1;
}

/****************************************************/
static status_t luawindowbase_destroy(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    status_t ret0 = pluawindowbase->Destroy();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_attachwnd(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    HWND hwnd = (HWND)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->AttachWnd(hwnd);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_settext(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);

    size_t len = 0;
    const char* str = lua_tolstring(L,2,&len);
    if(!str || len <= 0)
    {
        pluawindowbase->SetText(L"");
        return 0;
    }
	
    CMem mem_str;
    mem_str.Init();
    mem_str.SetRawBuf((char*)str,len,true);

    CMem uni;
    uni.Init();
    uni.Malloc(len*sizeof(uint16_t));

    CEncoder::Utf8ToUnicode(&mem_str,&uni);
    pluawindowbase->SetText(uni.CStrW());
    return 0;
}

static status_t luawindowbase_gettext(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    CMem *text = get_mem(L,2);
    ASSERT(text);
    status_t ret0 = pluawindowbase->GetText_File(text);
    CEncoder::UnicodeToUtf8(text);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_movewindow(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    int32_t x = (int32_t)lua_tointeger(L,2);
    int32_t y = (int32_t)lua_tointeger(L,3);
    int32_t w = (int32_t)lua_tointeger(L,4);
    int32_t h = (int32_t)lua_tointeger(L,5);
    status_t ret0 = pluawindowbase->MoveWindow(x,y,w,h);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_show(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    status_t ret0 = pluawindowbase->Show();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_hide(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    status_t ret0 = pluawindowbase->Hide();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_gettextlen(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    int ret0 = pluawindowbase->GetTextLen();
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t luawindowbase_setparent(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    HWND hp = (HWND)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->SetParent(hp);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_getwidth(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    status_t ret0 = pluawindowbase->GetWidth();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_getheight(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    status_t ret0 = pluawindowbase->GetHeight();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_setstockfont(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    int32_t stock_font = (int32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->SetStockFont(stock_font);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_getstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t ret0 = pluawindowbase->GetStyle();
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t luawindowbase_getexstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t ret0 = pluawindowbase->GetExStyle();
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t luawindowbase_isvisible(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    bool ret0 = pluawindowbase->IsVisible()!=0;
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_setstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t style = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->SetStyle(style);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_addstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t style = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->AddStyle(style);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_removestyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t style = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->RemoveStyle(style);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_setexstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t ex_style = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->SetExStyle(ex_style);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_addexstyle(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t ex_style = (uint32_t)lua_tointeger(L,2);
    status_t ret0 = pluawindowbase->AddExStyle(ex_style);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_getparent(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    HWND ret0 = pluawindowbase->GetParent();
    lua_pushinteger(L,(lua_Integer)ret0);
    return 1;
}
static status_t luawindowbase_ismycommand(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t wparam = (uint32_t)lua_tointeger(L,2);
    bool ret0 = pluawindowbase->IsMyCommand(wparam)!=0;
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_ismynotify(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t lparam = (uint32_t)lua_tointeger(L,2);
    bool ret0 = pluawindowbase->IsMyNotify(lparam)!=0;
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luawindowbase_getnotifycode(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t lparam = (uint32_t)lua_tointeger(L,2);
    uint32_t ret0 = pluawindowbase->GetNotifyCode(lparam);
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t luawindowbase_getcommandcode(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    uint32_t wparam = (uint32_t)lua_tointeger(L,2);
    uint32_t ret0 = pluawindowbase->GetCommandCode(wparam);
    lua_pushinteger(L,ret0);
    return 1;
}
static status_t luawindowbase_gethwnd(lua_State *L)
{
    CLuaWindowBase *pluawindowbase = get_luawindowbase(L,1);
    ASSERT(pluawindowbase);
    HWND ret0 = pluawindowbase->hwnd;
    lua_pushinteger(L,(lua_Integer)ret0);
    return 1;
}
/****************************************************/
static const luaL_Reg luawindowbase_funcs_[] = {
    {"__gc",luawindowbase_gc_},
    {"__tostring",luawindowbase_tostring_},
    {"__is_same",luawindowbase_issame_},
    {"Destroy",luawindowbase_destroy},
    {"AttachWnd",luawindowbase_attachwnd},
    {"SetText",luawindowbase_settext},
    {"GetText",luawindowbase_gettext},
    {"MoveWindow",luawindowbase_movewindow},
    {"Show",luawindowbase_show},
    {"Hide",luawindowbase_hide},
    {"GetTextLen",luawindowbase_gettextlen},
    {"SetParent",luawindowbase_setparent},
    {"GetWidth",luawindowbase_getwidth},
    {"GetHeight",luawindowbase_getheight},
    {"SetStockFont",luawindowbase_setstockfont},
    {"GetStyle",luawindowbase_getstyle},
    {"GetExStyle",luawindowbase_getexstyle},
    {"IsVisible",luawindowbase_isvisible},
    {"SetStyle",luawindowbase_setstyle},
    {"AddStyle",luawindowbase_addstyle},
    {"RemoveStyle",luawindowbase_removestyle},
    {"SetExStyle",luawindowbase_setexstyle},
    {"AddExStyle",luawindowbase_addexstyle},
    {"GetParent",luawindowbase_getparent},
    {"IsMyCommand",luawindowbase_ismycommand},
    {"IsMyNotify",luawindowbase_ismynotify},
    {"GetNotifyCode",luawindowbase_getnotifycode},
    {"GetCommandCode",luawindowbase_getcommandcode},
    {"GetHWnd",luawindowbase_gethwnd},
    {NULL,NULL},
};

const luaL_Reg* get_luawindowbase_funcs()
{
    return luawindowbase_funcs_;
}

static int luaL_register_luawindowbase(lua_State *L)
{	
    static luaL_Reg _luawindowbase_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_luawindowbase_funcs_,&_index,get_luawindowbase_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LUAWINDOWBASE);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_luawindowbase_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_luawindowbase_funcs_);
    return 1;
}        

int luaopen_luawindowbase(lua_State *L)
{
    luaL_requiref(L, "LuaWindowBase",luaL_register_luawindowbase,1);
    lua_pop(L, 1);
    return 0;
}        


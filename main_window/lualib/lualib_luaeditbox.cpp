#include "lualib_luaeditbox.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_luawindowbase.h"

static bool luaeditbox_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CLuaEditBox *p = (CLuaEditBox*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_luaeditbox(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LUAEDITBOX,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return luaeditbox_is_userdata_valid(ud);  
}

CLuaEditBox *get_luaeditbox(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_luaeditbox(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CLuaEditBox *)ud->p;
} 

lua_userdata *luaeditbox_new_userdata(lua_State *L,CLuaEditBox *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_LUAEDITBOX);
    lua_setmetatable(L,-2);
    return ud;
}

static int luaeditbox_gc_(lua_State *L)
{
    if(!is_luaeditbox(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CLuaEditBox *pluaeditbox = (CLuaEditBox*)ud->p;
        DEL(pluaeditbox);
    }
    return 0;
}

static int luaeditbox_issame_(lua_State *L)
{
    CLuaEditBox *pluaeditbox1 = get_luaeditbox(L,1);
    ASSERT(pluaeditbox1);
    CLuaEditBox *pluaeditbox2 = get_luaeditbox(L,2);
    ASSERT(pluaeditbox2);
    int is_same = (pluaeditbox1==pluaeditbox2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int luaeditbox_tostring_(lua_State *L)
{
    CLuaEditBox *pluaeditbox = get_luaeditbox(L,1);
    char buf[1024];
    sprintf(buf,"userdata:luaeditbox:%p",pluaeditbox);
    lua_pushstring(L,buf);
    return 1;
}

/****************************************************/
static status_t luaeditbox_new(lua_State *L)
{
    CLuaEditBox *pluaeditbox;
    NEW(pluaeditbox,CLuaEditBox);
    pluaeditbox->Init();
    luaeditbox_new_userdata(L,pluaeditbox,0);
    return 1;
}

static status_t luaeditbox_create(lua_State *L)
{
    CLuaEditBox *pluaeditbox = get_luaeditbox(L,1);
    ASSERT(pluaeditbox);
    status_t ret0 = pluaeditbox->Create();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t luaeditbox_setmaxtext(lua_State *L)
{
    CLuaEditBox *pluaeditbox = get_luaeditbox(L,1);
    ASSERT(pluaeditbox);
    int max = (int)lua_tointeger(L,2);
    status_t ret0 = pluaeditbox->SetMaxText(max);
    lua_pushboolean(L,ret0);
    return 1;
}
static status_t editbox_setsel(lua_State *L)
{
    CLuaEditBox *peditbox = get_luaeditbox(L,1);
    ASSERT(peditbox);
    int s = (int)lua_tointeger(L,2);
    int e = (int)lua_tointeger(L,3);
    status_t ret0 = peditbox->SetSel(s,e);
    lua_pushboolean(L,ret0);
    return 1;
}

/****************************************************/
static const luaL_Reg luaeditbox_funcs_[] = {
    {"__gc",luaeditbox_gc_},
    {"__tostring",luaeditbox_tostring_},
    {"__is_same",luaeditbox_issame_},
    {"new",luaeditbox_new},
    {"Create",luaeditbox_create},
    {"SetMaxText",luaeditbox_setmaxtext},
    {"SetSel",editbox_setsel},
    {NULL,NULL},
};

const luaL_Reg* get_luaeditbox_funcs()
{
    return luaeditbox_funcs_;
}

static int luaL_register_luaeditbox(lua_State *L)
{	
    static luaL_Reg _luaeditbox_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_luaeditbox_funcs_,&_index,get_luawindowbase_funcs(),false);
    CLuaVm::CombineLuaFuncTable(_luaeditbox_funcs_,&_index,get_luaeditbox_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LUAEDITBOX);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_luaeditbox_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_luaeditbox_funcs_);
    return 1;
}        

int luaopen_luaeditbox(lua_State *L)
{
    luaL_requiref(L, "EditBox",luaL_register_luaeditbox,1);
    lua_pop(L, 1);
    return 0;
}        


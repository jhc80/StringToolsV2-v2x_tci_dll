#include "lualib_luabutton.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_luawindowbase.h"

static bool luabutton_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CHECK_IS_UD_READABLE(CLuaButton,ud);
    CLuaButton *p = (CLuaButton*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_luabutton(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LUABUTTON,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return luabutton_is_userdata_valid(ud);  
}

CLuaButton *get_luabutton(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_luabutton(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CLuaButton *)ud->p;
} 

lua_userdata *luabutton_new_userdata(lua_State *L,CLuaButton *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_LUABUTTON);
    lua_setmetatable(L,-2);
    return ud;
}

static int luabutton_gc_(lua_State *L)
{
    if(!is_luabutton(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CLuaButton *pluabutton = (CLuaButton*)ud->p;
        DEL(pluabutton);
    }
    return 0;
}

static int luabutton_issame_(lua_State *L)
{
    CLuaButton *pluabutton1 = get_luabutton(L,1);
    ASSERT(pluabutton1);
    CLuaButton *pluabutton2 = get_luabutton(L,2);
    ASSERT(pluabutton2);
    int is_same = (pluabutton1==pluabutton2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int luabutton_tostring_(lua_State *L)
{
    CLuaButton *pluabutton = get_luabutton(L,1);
    char buf[1024];
    sprintf(buf,"userdata:luabutton:%p",pluabutton);
    lua_pushstring(L,buf);
    return 1;
}

/****************************************************/
static status_t luabutton_new(lua_State *L)
{
    CLuaButton *pluabutton;
    NEW(pluabutton,CLuaButton);
    pluabutton->Init();
    luabutton_new_userdata(L,pluabutton,0);
    return 1;
}

static status_t luabutton_create(lua_State *L)
{
    CLuaButton *pluabutton = get_luabutton(L,1);
    ASSERT(pluabutton);
    status_t ret0 = pluabutton->Create();
    lua_pushboolean(L,ret0);
    return 1;
}

/****************************************************/
static const luaL_Reg luabutton_funcs_[] = {
    {"__gc",luabutton_gc_},
    {"__tostring",luabutton_tostring_},
    {"__is_same",luabutton_issame_},
    {"new",luabutton_new},
    {"Create",luabutton_create},
    {NULL,NULL},
};

const luaL_Reg* get_luabutton_funcs()
{
    return luabutton_funcs_;
}

static int luaL_register_luabutton(lua_State *L)
{	
    static luaL_Reg _luabutton_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_luabutton_funcs_,&_index,get_luawindowbase_funcs(),false);
    CLuaVm::CombineLuaFuncTable(_luabutton_funcs_,&_index,get_luabutton_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LUABUTTON);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_luabutton_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_luabutton_funcs_);
    return 1;
}        

int luaopen_luabutton(lua_State *L)
{
    luaL_requiref(L, "Button",luaL_register_luabutton,1);
    lua_pop(L, 1);
    return 0;
}        


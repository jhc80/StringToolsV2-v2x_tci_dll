#include "lualib_luaeditbox.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_luawindowbase.h"

LUA_IS_VALID_USER_DATA_FUNC(CLuaEditBox,luaeditbox)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CLuaEditBox,luaeditbox)
LUA_NEW_USER_DATA_FUNC(CLuaEditBox,luaeditbox,LUAEDITBOX)
LUA_GC_FUNC(CLuaEditBox,luaeditbox)
LUA_IS_SAME_FUNC(CLuaEditBox,luaeditbox)
LUA_TO_STRING_FUNC(CLuaEditBox,luaeditbox)

bool is_luaeditbox(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LUAEDITBOX,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return luaeditbox_is_userdata_valid(ud);  
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


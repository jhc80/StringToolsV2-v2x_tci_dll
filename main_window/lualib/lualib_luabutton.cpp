#include "lualib_luabutton.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_luawindowbase.h"

LUA_IS_VALID_USER_DATA_FUNC(CLuaButton,luabutton)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CLuaButton,luabutton)
LUA_NEW_USER_DATA_FUNC(CLuaButton,luabutton,LUABUTTON)
LUA_GC_FUNC(CLuaButton,luabutton)
LUA_IS_SAME_FUNC(CLuaButton,luabutton)
LUA_TO_STRING_FUNC(CLuaButton,luabutton)

bool is_luabutton(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LUABUTTON,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return luabutton_is_userdata_valid(ud);  
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


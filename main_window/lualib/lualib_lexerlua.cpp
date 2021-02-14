#include "lualib_lexerlua.h"
#include "lualib_filebase.h"
#include "lualib_lexer.h"
#include "mem_tool.h"
#include "syslog.h"

LUA_IS_VALID_USER_DATA_FUNC(CLexerLua,lexerlua)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CLexerLua,lexerlua)
LUA_NEW_USER_DATA_FUNC(CLexerLua,lexerlua,LEXERLUA)
LUA_GC_FUNC(CLexerLua,lexerlua)
LUA_IS_SAME_FUNC(CLexerLua,lexerlua)
LUA_TO_STRING_FUNC(CLexerLua,lexerlua)

bool is_lexerlua(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LEXERLUA,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return lexerlua_is_userdata_valid(ud);  
}

/****************************************/
static status_t lexerlua_new(lua_State *L)
{
    CLexerLua *plexerlua;
    NEW(plexerlua,CLexerLua);
    plexerlua->Init();
    lexerlua_new_userdata(L,plexerlua,0);
    return 1;
}

static status_t lexerlua_destroy(lua_State *L)
{
	CLexerLua *plexerlua = get_lexerlua(L,1);
	ASSERT(plexerlua);
	plexerlua->Destroy();
	return 0;
}

static int lexerlua_nexttoken(lua_State *L)
{
	CLexerLua *plexerlua = get_lexerlua(L,1);
	ASSERT(plexerlua);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexerlua->NextToken(out);
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int lexerlua_lexer(lua_State *L)
{
	CLexerLua *plexerlua = get_lexerlua(L,1);
	ASSERT(plexerlua);
	CLexer *_ret_0 = (CLexer*)plexerlua;
	if(_ret_0==NULL)return 0;
	lexer_new_userdata(L,_ret_0,1);
	return 1;
}
static const luaL_Reg lexerlua_lib[] = {
	{"new",lexerlua_new},
	{"__gc",lexerlua_gc_},
	{"__tostring",lexerlua_tostring_},
	{"__is_same",lexerlua_issame_},
	{"NextToken",lexerlua_nexttoken},
	{"Lexer",lexerlua_lexer},
	{"Destroy",lexerlua_destroy},
	{NULL, NULL}
};

const luaL_Reg* get_lexerlua_funcs()
{
    return lexerlua_lib;
}

static int luaL_register_lexerlua(lua_State *L)
{	
    static luaL_Reg _lexerlua_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_lexerlua_funcs_,&_index,get_lexer_funcs(),false);
    CLuaVm::CombineLuaFuncTable(_lexerlua_funcs_,&_index,get_lexerlua_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LEXERLUA);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_lexerlua_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_lexerlua_funcs_);
    return 1;
}        

int luaopen_lexerlua(lua_State *L)
{
    luaL_requiref(L, "LexerLua",luaL_register_lexerlua,1);
    lua_pop(L, 1);
    return 0;
}        

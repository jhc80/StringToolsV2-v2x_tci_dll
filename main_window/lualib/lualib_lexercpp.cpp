#include "lualib_lexercpp.h"
#include "lualib_filebase.h"
#include "lualib_lexer.h"
#include "mem_tool.h"
#include "syslog.h"

LUA_IS_VALID_USER_DATA_FUNC(CLexerCpp,lexercpp)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CLexerCpp,lexercpp)
LUA_NEW_USER_DATA_FUNC(CLexerCpp,lexercpp,LEXERCPP)
LUA_GC_FUNC(CLexerCpp,lexercpp)
LUA_IS_SAME_FUNC(CLexerCpp,lexercpp)
LUA_TO_STRING_FUNC(CLexerCpp,lexercpp)

bool is_lexercpp(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LEXERCPP,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return lexercpp_is_userdata_valid(ud);  
}
/****************************************/
static status_t lexercpp_new(lua_State *L)
{
    CLexerCpp *plexercpp;
    NEW(plexercpp,CLexerCpp);
    plexercpp->Init();
    lexercpp_new_userdata(L,plexercpp,0);
    return 1;
}

static int lexercpp_nexttoken(lua_State *L)
{
	CLexerCpp *plexercpp = get_lexercpp(L,1);
	ASSERT(plexercpp);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexercpp->NextToken(out);
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int lexercpp_lexer(lua_State *L)
{
	CLexerCpp *plexercpp = get_lexercpp(L,1);
	ASSERT(plexercpp);	
	lexer_new_userdata(L,plexercpp,1);
	return 1;
}
static const luaL_Reg lexercpp_lib[] = {
	{"new",lexercpp_new},
	{"__gc",lexercpp_gc_},
	{"__tostring",lexercpp_tostring_},
	{"IsSame",lexercpp_issame_},
	{"NextToken",lexercpp_nexttoken},
	{"Lexer",lexercpp_lexer},
	{NULL, NULL}
};

const luaL_Reg* get_lexercpp_funcs()
{
    return lexercpp_lib;
}

static int luaL_register_lexercpp(lua_State *L)
{	
    static luaL_Reg _lexercpp_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_lexercpp_funcs_,&_index,get_lexer_funcs(),false);
    CLuaVm::CombineLuaFuncTable(_lexercpp_funcs_,&_index,get_lexercpp_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LEXERCPP);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_lexercpp_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_lexercpp_funcs_);
    return 1;
}        

int luaopen_lexercpp(lua_State *L)
{
    luaL_requiref(L, "LexerCpp",luaL_register_lexercpp,1);
    lua_pop(L, 1);
    return 0;
}        


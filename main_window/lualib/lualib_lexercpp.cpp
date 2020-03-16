#include "lualib_lexercpp.h"
#include "lualib_filebase.h"
#include "lualib_lexer.h"
#include "mem_tool.h"
#include "syslog.h"

static bool lexercpp_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CHECK_IS_UD_READABLE(CLexerCpp,ud);
    CLexerCpp *p = (CLexerCpp*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_lexercpp(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LEXERCPP,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return lexercpp_is_userdata_valid(ud);  
}

CLexerCpp *get_lexercpp(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_lexercpp(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CLexerCpp *)ud->p;
} 

lua_userdata *lexercpp_new_userdata(lua_State *L,CLexerCpp *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_LEXERCPP);
    lua_setmetatable(L,-2);
    return ud;
}

static int lexercpp_gc_(lua_State *L)
{
    if(!is_lexercpp(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CLexerCpp *plexercpp = (CLexerCpp*)ud->p;
        DEL(plexercpp);
    }
    return 0;
}

static int lexercpp_issame_(lua_State *L)
{
    CLexerCpp *plexercpp1 = get_lexercpp(L,1);
    ASSERT(plexercpp1);
    CLexerCpp *plexercpp2 = get_lexercpp(L,2);
    ASSERT(plexercpp2);
    int is_same = (plexercpp1==plexercpp2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int lexercpp_tostring_(lua_State *L)
{
    CLexerCpp *plexercpp = get_lexercpp(L,1);
    char buf[1024];
    sprintf(buf,"userdata:lexercpp:%p",plexercpp);
    lua_pushstring(L,buf);
    return 1;
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


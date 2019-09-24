#include "lualib_lexerlua.h"
#include "lualib_filebase.h"
#include "lualib_lexer.h"
#include "mem_tool.h"
#include "syslog.h"

static bool lexerlua_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CLexerLua *p = (CLexerLua*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_lexerlua(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LEXERLUA,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return lexerlua_is_userdata_valid(ud);  
}

CLexerLua *get_lexerlua(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_lexerlua(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CLexerLua *)ud->p;
} 

lua_userdata *lexerlua_new_userdata(lua_State *L,CLexerLua *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_LEXERLUA);
    lua_setmetatable(L,-2);
    return ud;
}

static int lexerlua_gc_(lua_State *L)
{
    if(!is_lexerlua(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CLexerLua *plexerlua = (CLexerLua*)ud->p;
        DEL(plexerlua);
    }
    return 0;
}

static int lexerlua_issame_(lua_State *L)
{
    CLexerLua *plexerlua1 = get_lexerlua(L,1);
    ASSERT(plexerlua1);
    CLexerLua *plexerlua2 = get_lexerlua(L,2);
    ASSERT(plexerlua2);
    int is_same = (plexerlua1==plexerlua2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int lexerlua_tostring_(lua_State *L)
{
    CLexerLua *plexerlua = get_lexerlua(L,1);
    char buf[1024];
    sprintf(buf,"userdata:lexerlua:%p",plexerlua);
    lua_pushstring(L,buf);
    return 1;
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
	{"IsSame",lexerlua_issame_},
	{"NextToken",lexerlua_nexttoken},
	{"Lexer",lexerlua_lexer},
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

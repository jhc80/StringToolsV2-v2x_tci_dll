#include "lualib_lexer.h"
#include "lualib_filebase.h"
#include "lualib_lexercpp.h"
#include "lualib_lexerlua.h"
#include "mem_tool.h"
#include "syslog.h"

LUA_IS_VALID_USER_DATA_FUNC(CLexer,lexer)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CLexer,lexer)
LUA_NEW_USER_DATA_FUNC(CLexer,lexer,LEXER)
LUA_GC_FUNC(CLexer,lexer)
LUA_IS_SAME_FUNC(CLexer,lexer)
LUA_TO_STRING_FUNC(CLexer,lexer)


bool is_lexer(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_LEXER,
        LUA_USERDATA_LEXERCPP,
        LUA_USERDATA_LEXERLUA,
    };            
    lua_userdata *ud = NULL;
    for(int i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return lexer_is_userdata_valid(ud);  
}

/****************************************/
static status_t lexer_new(lua_State *L)
{
    CLexer *plexer;
    NEW(plexer,CLexer);
    plexer->Init();
    lexer_new_userdata(L,plexer,0);
    return 1;
}

static int lexer_reporterror(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	int _ret_0 = (int)plexer->ReportError();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_reset(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	int _ret_0 = (int)plexer->Reset();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_readword(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexer->ReadWord(out);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_readempty(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexer->ReadEmpty(out);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_restorecontext(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	const char* context = (const char*)lua_tostring(L,2);
	ASSERT(context);

	int _ret_0 = (int)plexer->RestoreContext((LexContext*)context);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_savecontext(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	LexContext context;
	plexer->SaveContext(&context);	
	lua_pushlstring(L,(const char*)&context,sizeof(context));
	return 1;
}
static int lexer_readnumber(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexer->ReadNumber(out);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_readquotestr(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *file = get_filebase(L,2);
	ASSERT(file);
	int escape_char = (int)lua_tointeger(L,3);
	int end_char = (int)lua_tointeger(L,4);
	int _ret_0 = (int)plexer->ReadQuoteStr(file,escape_char,end_char);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_readcstylecomments(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *out = get_filebase(L,2);
	ASSERT(out);
	int _ret_0 = (int)plexer->ReadCStyleComments(out);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_isend(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	int _ret_0 = (int)plexer->IsEnd();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int lexer_getcurrentline(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	int _ret_0 = (int)plexer->GetCurrentLine();
	lua_pushinteger(L,_ret_0);
	return 1;
}
static int lexer_loadfile_v1(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	CFileBase *file = get_filebase(L,2);
	ASSERT(file);
	int _ret_0 = (int)plexer->LoadFile(file);
	lua_pushboolean(L,_ret_0);
	return 1;
}

static int lexer_loadfile_v2(lua_State *L)
{
	CLexer *plexer = get_lexer(L,1);
	ASSERT(plexer);
	const char* filename = (const char*)lua_tostring(L,2);
	ASSERT(filename);
	int _ret_0 = (int)plexer->LoadFile(filename);
	lua_pushboolean(L,_ret_0);
	return 1;
}

static int lexer_loadfile(lua_State *L)
{
	if(lua_isstring(L,2))
		return lexer_loadfile_v2(L);
	else
		return lexer_loadfile_v1(L);
}

static int lexer_loadstring(lua_State *L)
{
    CLexer *plexer = get_lexer(L,1);
    ASSERT(plexer);
    size_t size = 0;
    const char* str = lua_tolstring(L,2,&size);
    ASSERT(str);

    plexer->m_TmpFile.Destroy();
    plexer->m_TmpFile.Init();
    plexer->m_TmpFile.Write(str,size);
    plexer->i_SrcFile = &plexer->m_TmpFile;
	plexer->m_CurLine = 0;

    return 0;
}


static const luaL_Reg lexer_lib[] = {
	{"new",lexer_new},
	{"__gc",lexer_gc_},
	{"__tostring",lexer_tostring_},
	{"__is_same",lexer_issame_},
	{"ReportError",lexer_reporterror},
	{"Reset",lexer_reset},
	{"ReadWord",lexer_readword},
	{"ReadEmpty",lexer_readempty},
	{"RestoreContext",lexer_restorecontext},
	{"SaveContext",lexer_savecontext},
	{"ReadNumber",lexer_readnumber},
	{"ReadQuoteStr",lexer_readquotestr},
	{"ReadCStyleComments",lexer_readcstylecomments},
	{"IsEnd",lexer_isend},
	{"GetCurrentLine",lexer_getcurrentline},
	{"LoadFile",lexer_loadfile},
    {"LoadString",lexer_loadstring},
	{NULL, NULL}
};

const luaL_Reg* get_lexer_funcs()
{
    return lexer_lib;
}

static int luaL_register_lexer(lua_State *L)
{	
    static luaL_Reg _lexer_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_lexer_funcs_,&_index,get_lexer_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_LEXER);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_lexer_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_lexer_funcs_);
    return 1;
}        

int luaopen_lexer(lua_State *L)
{
    luaL_requiref(L, "Lexer",luaL_register_lexer,1);
    lua_pop(L, 1);
    return 0;
}        


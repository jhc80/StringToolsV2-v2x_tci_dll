#include "lualib_idlparser.h"
#include "lualib_filebase.h"
#include "mem_tool.h"
#include "syslog.h"

LUA_IS_VALID_USER_DATA_FUNC(CIdlParser,idlparser)
LUA_GET_OBJ_FROM_USER_DATA_FUNC(CIdlParser,idlparser)
LUA_NEW_USER_DATA_FUNC(CIdlParser,idlparser,IDLPARSER)
LUA_GC_FUNC(CIdlParser,idlparser)
LUA_IS_SAME_FUNC(CIdlParser,idlparser)
LUA_TO_STRING_FUNC(CIdlParser,idlparser)

bool is_idlparser(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_IDLPARSER,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return idlparser_is_userdata_valid(ud);  
}
/****************************************/
static status_t idlparser_new(lua_State *L)
{
    CIdlParser *pidlparser;
    NEW(pidlparser,CIdlParser);
    pidlparser->Init();
    idlparser_new_userdata(L,pidlparser,0);
    return 1;
}

static int idlparser_getuncertainerrors(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
	
    CMemFile *mf_err = pidlparser->GetUncertainErrors();
    ASSERT(mf_err);

    AUTO_LOCAL_MEM(mem,mf_err->GetSize());
    mem.Puts(mf_err);
	
	lua_pushlstring(L,mem.CStr(),mem.StrLen());
	return 1;
}
static int idlparser_getcertainerrors(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
    
    CMemFile *mf_err = pidlparser->GetCertainErrors();
    ASSERT(mf_err);

    AUTO_LOCAL_MEM(mem,mf_err->GetSize());
    mem.Puts(mf_err);
    
    lua_pushlstring(L,mem.CStr(),mem.StrLen());
	return 1;
}
static int idlparser_haserrors(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
	int _ret_0 = (int)pidlparser->HasErrors();
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int idlparser_parseall(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
    CIdlModule module;
    module.Init();
	
    int ok = pidlparser->ParseAll(&module);    

    if(!ok) return 0;

    if(pidlparser->HasErrors())
        return 0;

    CMemFile mf;
    mf.Init();

    module.ToLua(&mf);

    AUTO_LOCAL_MEM(mem,mf.GetSize());

    mem.SetSize(0);
    mem.Puts(&mf);
	
	lua_pushlstring(L,mem.CStr(),mem.StrLen());
	return 1;
}
static int idlparser_loadsourcefromstring(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
	const char* str = (const char*)lua_tostring(L,2);
	ASSERT(str);
    
    CMem tmp(str);
	int _ret_0 = (int)pidlparser->LoadSource(&tmp);

	lua_pushboolean(L,_ret_0);
	return 1;
}
static int idlparser_loadsourcefromfile_v1(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
	CFileBase *file = get_filebase(L,2);
	ASSERT(file);
	int _ret_0 = (int)pidlparser->LoadSource(file);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int idlparser_loadsourcefromfile_v2(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	ASSERT(pidlparser);
	const char* filename = (const char*)lua_tostring(L,2);
	ASSERT(filename);
	int _ret_0 = (int)pidlparser->LoadSource(filename);
	lua_pushboolean(L,_ret_0);
	return 1;
}
static int idlparser_loadsourcefromfile(lua_State *L)
{
    if(lua_isstring(L,2))
        return idlparser_loadsourcefromfile_v2(L);
    else
        return idlparser_loadsourcefromfile_v1(L);
}

static const luaL_Reg idlparser_lib[] = {
    {"__gc",idlparser_gc_},
    {"__tostring",idlparser_tostring_},
    {"__is_same",idlparser_issame_},
    {"new",idlparser_new},

	{"GetUncertainErrors",idlparser_getuncertainerrors},
	{"GetCertainErrors",idlparser_getcertainerrors},
	{"HasErrors",idlparser_haserrors},
	{"ParseAll",idlparser_parseall},
	{"LoadSourceFromString",idlparser_loadsourcefromstring},
	{"LoadSourceFromFile",idlparser_loadsourcefromfile},
	{NULL, NULL}
};
static int luaL_register_idlparser(lua_State *L)
{	
	luaL_newmetatable(L, LUA_USERDATA_IDLPARSER);
	lua_pushvalue(L, -1);	
	lua_setfield(L, -2, "__index");	
	luaL_setfuncs(L,idlparser_lib,0);
	lua_pop(L, 1);
	luaL_newlib(L,idlparser_lib);
	return 1;
}

int luaopen_idlparser(lua_State *L)
{
	luaL_requiref(L, "IdlParser",luaL_register_idlparser,1);
	lua_pop(L, 1);
	return 0;
}

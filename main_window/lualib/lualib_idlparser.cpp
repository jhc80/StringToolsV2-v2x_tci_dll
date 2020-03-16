#include "lualib_idlparser.h"
#include "lualib_filebase.h"
#include "mem_tool.h"
#include "syslog.h"

static bool idlparser_is_userdata_valid(lua_userdata *ud)
{
	if(ud == NULL)return false;
	if(ud->p == NULL)return false;
	if(ud->__weak_ref_id == 0) return false;
    CHECK_IS_UD_READABLE(CIdlParser,ud);
	CIdlParser *p = (CIdlParser*)ud->p;
	return p->__weak_ref_id == ud->__weak_ref_id;
}
bool is_idlparser(lua_State *L, int idx)
{
	lua_userdata *ud = (lua_userdata*)luaL_testudata(L, idx, LUA_USERDATA_IDLPARSER);
	return idlparser_is_userdata_valid(ud);
}
CIdlParser *get_idlparser(lua_State *L, int idx)
{
	lua_userdata *ud = (lua_userdata*)luaL_checkudata(L, idx, LUA_USERDATA_IDLPARSER);
	ASSERT(ud && ud->p);
	ASSERT(ud->__weak_ref_id != 0);
	CIdlParser *p = (CIdlParser*)ud->p;
	ASSERT(p->__weak_ref_id == ud->__weak_ref_id);
	return p;
}
lua_userdata *idlparser_new_userdata(lua_State *L,CIdlParser *pt,int is_weak)
{
	lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
	ASSERT(ud && pt);
	ud->p = pt;
	ud->is_attached = is_weak;
	ud->__weak_ref_id = pt->__weak_ref_id;
	luaL_getmetatable(L,LUA_USERDATA_IDLPARSER);
	lua_setmetatable(L,-2);
	return ud;
}

static int idlparser_new(lua_State *L)
{
	CIdlParser *pt;
	NEW(pt,CIdlParser);
	pt->Init();
	idlparser_new_userdata(L,pt,0);
	return 1;
}

static int idlparser_destroy(lua_State *L)
{
	lua_userdata *ud = (lua_userdata*)luaL_checkudata(L, 1, LUA_USERDATA_IDLPARSER);
	if(!idlparser_is_userdata_valid(ud))
		return 0;
	CIdlParser *pidlparser = (CIdlParser*)ud->p;
	if(!(ud->is_attached))
	{
		DEL(pidlparser);
	}
	return 0;
}
static int idlparser_issame(lua_State *L)
{
	CIdlParser *pidlparser1 = get_idlparser(L,1);
	ASSERT(pidlparser1);
	CIdlParser *pidlparser2 = get_idlparser(L,2);
	ASSERT(pidlparser2);
	int is_same = (pidlparser1==pidlparser2);
	lua_pushboolean(L,is_same);
	return 1;
}
static int idlparser_tostring(lua_State *L)
{
	CIdlParser *pidlparser = get_idlparser(L,1);
	char buf[1024];
	sprintf(buf,"userdata:idlparser:%p",pidlparser);
	lua_pushstring(L,buf);
	return 1;
}
/****************************************/
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
	{"new",idlparser_new},
	{"__gc",idlparser_destroy},
	{"__tostring",idlparser_tostring},
	{"IsSame",idlparser_issame},
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

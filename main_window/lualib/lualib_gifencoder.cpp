#include "lualib_gifencoder.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_ximage.h"
#include "lualib_filebase.h"

static bool gifencoder_is_userdata_valid(lua_userdata *ud)
{
    if(ud == NULL)return false;
    if(ud->p == NULL)return false;
    if(ud->__weak_ref_id == 0) return false;
    CHECK_IS_UD_READABLE(CGifEncoder,ud);
    CGifEncoder *p = (CGifEncoder*)ud->p;
    return p->__weak_ref_id == ud->__weak_ref_id;
}    

bool is_gifencoder(lua_State *L, int idx)
{        
    const char* ud_names[] = {
        LUA_USERDATA_GIFENCODER,
    };            
    lua_userdata *ud = NULL;
    for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
    {
        ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
        if(ud)break;
    }
    return gifencoder_is_userdata_valid(ud);  
}

CGifEncoder *get_gifencoder(lua_State *L, int idx)
{
    lua_userdata *ud = NULL;
    if(is_gifencoder(L,idx))
    {
        ud = (lua_userdata*)lua_touserdata(L,idx);		
    }
    ASSERT(ud);
    return (CGifEncoder *)ud->p;
} 

lua_userdata *gifencoder_new_userdata(lua_State *L,CGifEncoder *pobj,int is_weak)
{
    lua_userdata *ud = (lua_userdata*)lua_newuserdata(L,sizeof(lua_userdata));
    ASSERT(ud && pobj);
    ud->p = pobj;
    ud->is_attached = is_weak;
    ud->__weak_ref_id = pobj->__weak_ref_id;
    luaL_getmetatable(L,LUA_USERDATA_GIFENCODER);
    lua_setmetatable(L,-2);
    return ud;
}

static int gifencoder_gc_(lua_State *L)
{
    if(!is_gifencoder(L,1)) return 0;

    lua_userdata *ud = (lua_userdata*)lua_touserdata(L,1);		
    ASSERT(ud);

    if(!(ud->is_attached))
    {
        CGifEncoder *pgifencoder = (CGifEncoder*)ud->p;
        DEL(pgifencoder);
    }
    return 0;
}

static int gifencoder_issame_(lua_State *L)
{
    CGifEncoder *pgifencoder1 = get_gifencoder(L,1);
    ASSERT(pgifencoder1);
    CGifEncoder *pgifencoder2 = get_gifencoder(L,2);
    ASSERT(pgifencoder2);
    int is_same = (pgifencoder1==pgifencoder2);
    lua_pushboolean(L,is_same);
    return 1;
}

static int gifencoder_tostring_(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    char buf[1024];
    sprintf(buf,"userdata:gifencoder:%p",pgifencoder);
    lua_pushstring(L,buf);
    return 1;
}

/****************************************************/
static status_t gifencoder_new(lua_State *L)
{
    CGifEncoder *pgifencoder;
    NEW(pgifencoder,CGifEncoder);
    pgifencoder->Init();
    gifencoder_new_userdata(L,pgifencoder,0);
    return 1;
}

static status_t gifencoder_addframe(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    CxImage *img = get_ximage(L,2);
    ASSERT(img);
    status_t ret0 = pgifencoder->AddFrame(img);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_end(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    status_t ret0 = pgifencoder->End();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_begin_v1(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    const char* filename = (const char*)lua_tostring(L,2);
    ASSERT(filename);
    status_t ret0 = pgifencoder->Begin(filename);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_begin_v2(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    CFileBase *file = get_filebase(L,2);
    ASSERT(file);
    status_t ret0 = pgifencoder->Begin(file);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_destroy(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    status_t ret0 = pgifencoder->Destroy();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_getloops(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    int ret0 = pgifencoder->GetLoops();
    lua_pushinteger(L,ret0);
    return 1;
}

static status_t gifencoder_getlocaldispmeth(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    bool ret0 = pgifencoder->GetLocalDispMeth();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_getlocalcolormap(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    bool ret0 = pgifencoder->GetLocalColorMap();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_setloops(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    int _loops = (int)lua_tointeger(L,2);
    status_t ret0 = pgifencoder->SetLoops(_loops);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_setlocaldispmeth(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    bool _localdispmeth = lua_toboolean(L,2)!=0;
    status_t ret0 = pgifencoder->SetLocalDispMeth(_localdispmeth);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_setlocalcolormap(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    bool _localcolormap = lua_toboolean(L,2)!=0;
    status_t ret0 = pgifencoder->SetLocalColorMap(_localcolormap);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_setcomment(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    const char* comment = (const char*)lua_tostring(L,2);
    ASSERT(comment);
    status_t ret0 = pgifencoder->SetComment(comment);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_setdisposalmethod(lua_State *L)
{
    CGifEncoder *pgifencoder = get_gifencoder(L,1);
    ASSERT(pgifencoder);
    uint8_t dm = (uint8_t)lua_tointeger(L,2);
    status_t ret0 = pgifencoder->SetDisposalMethod(dm);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t gifencoder_begin(lua_State *L)
{
    if(is_filebase(L,2))
    {
        return gifencoder_begin_v2(L);
    }

    if(lua_isstring(L,2))
    {
        return gifencoder_begin_v1(L);
    }

    return 0;
}

/****************************************************/
static const luaL_Reg gifencoder_funcs_[] = {
    {"__gc",gifencoder_gc_},
    {"__tostring",gifencoder_tostring_},
    {"__is_same",gifencoder_issame_},
    {"SetDisposalMethod",gifencoder_setdisposalmethod},
    {"SetLocalDispMeth",gifencoder_setlocaldispmeth},
    {"SetComment",gifencoder_setcomment},
    {"SetLoops",gifencoder_setloops},
    {"Begin",gifencoder_begin},
    {"SetLocalColorMap",gifencoder_setlocalcolormap},
    {"AddFrame",gifencoder_addframe},
    {"GetLocalColorMap",gifencoder_getlocalcolormap},
    {"GetLoops",gifencoder_getloops},
    {"Destroy",gifencoder_destroy},
    {"GetLocalDispMeth",gifencoder_getlocaldispmeth},
    {"End",gifencoder_end},
    {"new",gifencoder_new},
    {NULL,NULL},
};

const luaL_Reg* get_gifencoder_funcs()
{
    return gifencoder_funcs_;
}

static int luaL_register_gifencoder(lua_State *L)
{	
    static luaL_Reg _gifencoder_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_gifencoder_funcs_,&_index,get_gifencoder_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_GIFENCODER);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_gifencoder_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_gifencoder_funcs_);
    return 1;
}        

int luaopen_gifencoder(lua_State *L)
{
    luaL_requiref(L, "GifEncoder",luaL_register_gifencoder,1);
    lua_pop(L, 1);
    return 0;
}        


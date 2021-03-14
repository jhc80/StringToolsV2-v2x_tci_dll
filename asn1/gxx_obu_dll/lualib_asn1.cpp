#include "lualib_asn1.h"
#include "mem_tool.h"
#include "syslog.h"
#include "lualib_filebase.h"
#include "asn_to_js_tree.h"
#include "asn_to_lua.h"
#include "asn_to_js.h"
#include "asn_to_json.h"
#include "lua_to_asn.h"
#include "constr_TYPE.h"
#include "luavm.h"

static status_t asn1_tolua(lua_State *L)
{
    CMem mem;
    mem.Init();

    size_t len = 0;
    const char *p = lua_tolstring(L,1,&len);
    
    ASSERT(p && len > 0);
    mem.SetRawBuf((void*)p,len,true);

    asn_TYPE_descriptor_t *descriptor = (asn_TYPE_descriptor_t*)lua_tointeger(L,2);
    ASSERT(descriptor);

    CAsnDescriptor desc;
    desc.Init();
    desc.Set(descriptor);

    void *frame = NULL;

    asn_dec_rval_t ret = uper_decode_complete(
        0, descriptor, (void **)&frame, 
        mem.GetRawBuf(),mem.GetSize());

    CMemFile out;
    out.Init();

    if (ret.code == RC_OK)
    {              
        int comma = 0;
        asn_to_lua(&desc,NULL,frame,0,&out,&comma);
        descriptor->op->free_struct(descriptor, frame, ASFM_FREE_EVERYTHING);
    }
    else
    {
        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
            "asn decode fail code = %d, consumed = %d",
            ret.code,ret.consumed
        );
    }

    if(out.GetSize() > 0)
    {
        CMem tmp;
        tmp.Init();
        tmp.Copy(&out);
        lua_pushlstring(L,tmp.CStr(),tmp.StrLen());
        return 1;
    }
    return 0;
}

static status_t asn1_fromlua(lua_State *L)
{    
    asn_TYPE_descriptor_t *descriptor = (asn_TYPE_descriptor_t*) lua_tointeger(L,2);
    ASSERT(descriptor);

    CAsnDescriptor desc;
    desc.Init();
    desc.Set(descriptor);

    uint8_t *ptr = NULL;
    ASSERT(lua_to_asn(&desc,L,1,&ptr));
    ASSERT(ptr);

    LOCAL_MEM_WITH_SIZE(buffer,32*1024);
    buffer.Zero();

	asn_enc_rval_t ret = uper_encode_to_buffer(
        descriptor, 0, ptr, 
        buffer.GetRawBuf(),buffer.GetMaxSize());    

    if(ret.encoded < 0)
    {
        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
            "ASN1.FromLua: asn1 encode error:%s",
            ret.failed_type->name
        );        
        return 0;
    }
    else
    {
        int bytes = (ret.encoded+7)/8;
        buffer.SetSize(bytes);
        descriptor->op->free_struct(descriptor, ptr, ASFM_FREE_EVERYTHING);    
    }

    lua_pushlstring(L,buffer.GetRawBuf(),buffer.GetSize());
    return 1;
}


extern asn_TYPE_descriptor_t *asn_pdu_collection[];

static status_t asn1_getdescriptor(lua_State *L)
{
    const char* name = (const char*)lua_tostring(L,1);
    ASSERT(name);

    void *addr = NULL;
    
    int i = 0;
    while(true)
    {
        if(asn_pdu_collection[i] == NULL)break;
        if(strcmp(asn_pdu_collection[i]->name,name) == 0)
        {
            addr = (void*)asn_pdu_collection[i];
            break;
        }
        i++;
    }

    if(addr == NULL)
    {
        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
            "unknown asn_DEF %s.",name
        );
    }

    lua_pushinteger(L,(lua_Integer)addr);
    return 1;
}

static status_t asn1_getalldescriptors(lua_State *L)
{
    int i = 1;
    lua_newtable(L); 
    int top = lua_gettop(L);
    while(true)
    {
        if(asn_pdu_collection[i] == NULL)break;
        lua_pushinteger(L,i);
        lua_pushstring(L,asn_pdu_collection[i]->name);
        lua_settable(L,top);
        i++;
    }
    return 1;
}

/****************************************************/
static const luaL_Reg asn1_funcs_[] = {
    {"GetDescriptor",asn1_getdescriptor},    
    {"GetAllDescriptors",asn1_getalldescriptors},    
    {"ToLua",asn1_tolua},    
    {"FromLua",asn1_fromlua},
    {NULL,NULL},
};

const luaL_Reg* get_asn1_funcs()
{
    return asn1_funcs_;
}

static int luaL_register_asn1(lua_State *L)
{	
    static luaL_Reg _asn1_funcs_[MAX_LUA_FUNCS];
    int _index = 0;        

    CLuaVm::CombineLuaFuncTable(_asn1_funcs_,&_index,get_asn1_funcs(),true);

    luaL_newmetatable(L, LUA_USERDATA_ASN1);
    lua_pushvalue(L, -1);	
    lua_setfield(L, -2, "__index");	
    luaL_setfuncs(L,_asn1_funcs_,0);	
    lua_pop(L, 1);
    luaL_newlib(L,_asn1_funcs_);
    return 1;
}        

DLL_EXPORT_C int luaopen_asn1_gxx_obu(lua_State *L)
{
    luaL_requiref(L, "Asn1GxxObu",luaL_register_asn1,1);
    lua_pop(L, 1);
    return 0;
}        


#include "asn1p_wsyntx_to_lua.h"
#include "asn1p_wsyntx_chunk_to_lua.h"
#include "asn1p_globals.h"

int asn1p_wsyntx_to_lua(struct asn1p_wsyntx_s *wsyntx)
{
    if(!wsyntx)return 0;

    CHECK_RECURSIVE_CALL(wsyntx);
    
    if(wsyntx->parent)
    {
        lua_log("parent = {");
        lua_inc_level(1);
        asn1p_wsyntx_chunk_to_lua(wsyntx->parent);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("chunks={");
    lua_inc_level(1);
    
    struct asn1p_wsyntx_chunk_s *chunk;

    TQ_FOR(chunk,&wsyntx->chunks,next)
    {
        lua_log("{");
        lua_inc_level(1);
        asn1p_wsyntx_chunk_to_lua(chunk);
        lua_inc_level(-1);
        lua_log("},");
    }
    lua_inc_level(-1);
    lua_log("},");

    

    return 1;
}

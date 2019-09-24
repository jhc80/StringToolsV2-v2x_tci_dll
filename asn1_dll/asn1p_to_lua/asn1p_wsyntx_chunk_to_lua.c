#include "asn1p_wsyntx_chunk_to_lua.h"
#include "asn1p_globals.h"

int asn1p_wsyntx_chunk_to_lua(struct asn1p_wsyntx_chunk_s *wsyntx_chunk)
{
    if(!wsyntx_chunk)return 0;
    
    CHECK_RECURSIVE_CALL(wsyntx_chunk);

    lua_log("type = %d,",wsyntx_chunk->type);

    lua_log("content = {");
    lua_inc_level(1);

    switch(wsyntx_chunk->type)
    {
        case WC_LITERAL:
        case WC_WHITESPACE:
        case WC_FIELD:
            lua_log("token = \"%s\"",wsyntx_chunk->content.token);
            break;
        case WC_OPTIONALGROUP:
            lua_log("syntax = {");
            lua_inc_level(1);
            asn1p_wsyntx_to_lua(wsyntx_chunk->content.syntax);
            lua_inc_level(-1);
            lua_log("},");
            break;
    }

    lua_inc_level(-1);
    lua_log("},");
    return 1;
}

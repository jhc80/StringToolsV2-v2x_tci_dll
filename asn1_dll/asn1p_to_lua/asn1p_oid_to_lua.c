#include "asn1p_oid_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_oid_arc_to_lua(struct asn1p_oid_arc_s* oid_arc) {
    if(!oid_arc) {
        return 0;
    }
    
    CHECK_RECURSIVE_CALL(oid_arc);

    lua_log("number=%jd,", oid_arc->number);
    if(oid_arc->name) {
        lua_log("name=\"%s\",", oid_arc->name);
    } else {
        // lua_log("name=nil,");
    }
    return 1;
}
int
asn1p_oid_to_lua(struct asn1p_oid_s* oid) {
    if(!oid) return 0;
    lua_inc_level(1);
    lua_log("arcs=");
    lua_log("{");
    if(oid->arcs) {
        lua_inc_level(1);

        asn1p_oid_arc_to_lua(oid->arcs);

        lua_inc_level(-1);
    }
    lua_log("},");
    lua_inc_level(-1);
    return 1;
}
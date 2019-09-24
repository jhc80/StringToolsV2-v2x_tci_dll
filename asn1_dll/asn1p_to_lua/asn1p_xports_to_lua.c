#include "asn1p_xports_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_xports_to_lua(struct asn1p_xports_s *xports) {
    if(!xports) return 0;

    CHECK_RECURSIVE_CALL(xports);

    lua_log("xports_type=%d,", xports->xports_type);
    if(xports->fromModuleName)
        lua_log("fromModuleName=\"%s\",", xports->fromModuleName);
    int pos = lua_current_position();
    int member_writter = 0;
    lua_log("identifier=");
    lua_log("{");
    lua_inc_level(1);
    if(xports->identifier.oid) {
        member_writter = 1;
        lua_log("oid=");
        lua_log("{");
        lua_inc_level(1);
        asn1p_oid_to_lua(xports->identifier.oid);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(xports->identifier.value) {
        member_writter = 1;
        lua_log("value=");
        lua_log("{");
        lua_inc_level(1);
        asn1p_value_to_lua(xports->identifier.value);
        lua_inc_level(-1);
        lua_log("}");
    }

    lua_inc_level(-1);
    lua_log("},");
    if(!member_writter) {
        lua_set_position(pos);
    }
    lua_log("xp_members=");
    lua_log("{");
    lua_inc_level(1);
    struct asn1p_expr_s *xp_member;
    TQ_FOR(xp_member, &xports->xp_members, next) {
        lua_log("{");
        lua_inc_level(1);
        asn1p_expr_to_lua(xp_member);
        lua_inc_level(-1);
        lua_log("},");
    }
    lua_inc_level(-1);
    lua_log("}");

    return 1;
}
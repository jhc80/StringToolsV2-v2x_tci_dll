#include "asn1p_value_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_value_to_lua(struct asn1p_value_s *value) {
    if(!value) return 0;

    CHECK_RECURSIVE_CALL(value);
    
    lua_log("type=%d,", value->type);
    lua_log("value=");
    lua_log("{");
    lua_inc_level(1);
    switch(value->type) {
    case ATV_TYPE: {
        lua_log("v_type=");
        lua_log("{");
        lua_inc_level(1);
        asn1p_expr_to_lua(value->value.v_type);
        lua_inc_level(-1);
        lua_log("},");
    } break;
    case ATV_VALUESET: {
        lua_log("constraint=");
        lua_log("{");
        lua_inc_level(1);
        asn1p_constraint_to_lua(value->value.constraint);
        lua_inc_level(-1);
        lua_log("},");

    } break;
    case ATV_REFERENCED: {
        lua_log("reference=");
        lua_log("{");
        lua_inc_level(1);
        asn1p_ref_to_lua(value->value.reference);
        lua_inc_level(-1);
        lua_log("},");
    } break;
    case ATV_INTEGER: {
        lua_log("v_integer=%d,", value->value.v_integer);
    } break;
    case ATV_REAL: {
        lua_log("v_double=%lf,", value->value.v_double);
    } break;
    case ATV_STRING: {
        lua_log("string=");
        lua_log("{");
        lua_inc_level(1);
        lua_log("buf=\"%s\",", value->value.string.buf);
        lua_log("size=%d,", value->value.string.size);
        lua_inc_level(-1);
        lua_log("},");
    } break;
    case ATV_BITVECTOR: {
        lua_log("binary_vector=");
        lua_log("{");
        lua_log("},");
    } break;
    case ATV_CHOICE_IDENTIFIER: {
        lua_log("choice_identifier=");
        lua_log("{");
        lua_inc_level(1);
        if(value->value.choice_identifier.identifier)
            lua_log("identifier=%s", value->value.choice_identifier.identifier);
        if(value->value.choice_identifier.value)
            asn1p_value_to_lua(value->value.choice_identifier.value);
        lua_inc_level(-1);
        lua_log("},");
    } break;
    default:
        break;
    }
    lua_inc_level(-1);
    lua_log("},");
    return 1;
}
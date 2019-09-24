#include "asn1p_ref_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_ref_to_lua(struct asn1p_ref_s *ref) {
    if(!ref) return 0;

    CHECK_RECURSIVE_CALL(ref);

    if(ref->components) {
        lua_log("components = {");
        lua_inc_level(1);
        lua_log("name = \"%s\",", ref->components->name);
        lua_log("lex_type = %d,", ref->components->lex_type);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("comp_count = %ld,", ref->comp_count);
    lua_log("comp_size = %ld,", ref->comp_size);
    if(ref->module) {
        lua_log("module = {");
        lua_inc_level(1);
        asn1p_module_to_lua(ref->module);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("_lineno = %d", ref->_lineno);

    return 1;
}
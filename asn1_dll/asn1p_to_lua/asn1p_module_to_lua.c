#include "asn1p_module_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_module_to_lua(struct asn1p_module_s *module) {
    if(module == NULL) return 0;

    CHECK_RECURSIVE_CALL(module);

    ///////////////////////////////////////
    lua_log("ModuleName=\"%s\",", module->ModuleName);
    ///////////////////////////////////////
    lua_log("source_file_name=[[%s]],", module->source_file_name);
    ///////////////////////////////////////
    if(module->module_oid) {
        lua_log("module_oid=");
        lua_log("{");
        asn1p_oid_to_lua(module->module_oid);
        lua_log("},");
    }

    ///////////////////////////////////////
    lua_log("module_flags=%d,", module->module_flags);
    ///////////////////////////////////////

    struct asn1p_xports_s *export, *import;
    if(!TQ_EMPTY(module, exports)) {
        lua_log("exports=");
        lua_log("{");
        lua_inc_level(1);
        TQ_FOR(export, &module->exports, xp_next) {
            lua_log("{");
            lua_inc_level(1);
            asn1p_xports_to_lua(export);
            lua_inc_level(-1);
            lua_log("},");
        }
        lua_inc_level(-1);
        lua_log("},");
    }
    ///////////////////////////////////////
    if(!TQ_EMPTY(module, imports)) {
        lua_log("imports=");
        lua_log("{");
        lua_inc_level(1);
        TQ_FOR(import, &module->imports, xp_next) {
            lua_log("{");
            lua_inc_level(1);
            asn1p_xports_to_lua(import);
            lua_inc_level(-1);
            lua_log("},");
        }
        lua_inc_level(-1);
        lua_log("},");
    }

    ///////////////////////////////////////
    if(!TQ_EMPTY(module, members)) {
        struct asn1p_expr_s *member;
        lua_log("members=");
        lua_log("{");
        lua_inc_level(1);
        TQ_FOR(member, &module->members, next) {
            lua_log("{");
            lua_inc_level(1);
            asn1p_expr_to_lua(member);
            lua_inc_level(-1);
            lua_log("},");
        }
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("asn1p=ALL_MODULES,");
    lua_log("_tags=%d,", module->_tags);

    return 1;
}
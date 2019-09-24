#include "asn1p_expr_to_lua.h"
#include "asn1p_globals.h"

int
asn1p_expr_to_lua(struct asn1p_expr_s *expr) {
    if(!expr) return 0;

    CHECK_RECURSIVE_CALL(expr);

    if(expr->Identifier) {
        lua_log("Identifier = \"%s\",", expr->Identifier);
    }

    lua_log("meta_type = %d,", expr->meta_type);
    lua_log("expr_type = %d,", expr->expr_type);

    if(expr->reference) {
        lua_log("reference = {");
        lua_inc_level(1);
        asn1p_ref_to_lua(expr->reference);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->constraints) {
        lua_log("constraints = {");
        lua_inc_level(1);
        asn1p_constraint_to_lua(expr->constraints);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->combined_constraints) {
        lua_log("combined_constraints = {");
        lua_inc_level(1);
        asn1p_constraint_to_lua(expr->combined_constraints);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->lhs_params) {
        lua_log("lhs_params = {");
        lua_inc_level(1);
        asn1p_paramlist_to_lua(expr->lhs_params);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->rhs_pspecs) {
        lua_log("rhs_pspecs = {");
        lua_inc_level(1);
        asn1p_expr_to_lua(expr->rhs_pspecs);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->specializations.pspecs_count > 0 && expr->specializations.pspec) {
        lua_log("specializations={");
        lua_inc_level(1);
        for(int i = 0; i < expr->specializations.pspecs_count; i++) {
            lua_log("{");
            lua_inc_level(1);

            if(expr->specializations.pspec->rhs_pspecs) {
                lua_log("rhs_pspecs={");
                lua_inc_level(1);
                asn1p_expr_to_lua(expr->specializations.pspec->rhs_pspecs);
                lua_inc_level(-1);
                lua_log("},");
            }

            if(expr->specializations.pspec->my_clone) {
                lua_log("my_clone={");
                lua_inc_level(1);
                asn1p_expr_to_lua(expr->specializations.pspec->my_clone);
                lua_inc_level(-1);
                lua_log("},");
            }

            lua_inc_level(-1);
            lua_log("},");
        }

        lua_inc_level(-1);
        lua_log("},");
    }


    lua_log("spec_index = %d,", expr->spec_index);

    if(expr->value) {
        lua_log("value = {");
        lua_inc_level(1);
        asn1p_value_to_lua(expr->value);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->with_syntax) {
        lua_log("with_syntax = {");
        lua_inc_level(1);
        asn1p_wsyntx_to_lua(expr->with_syntax);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->ioc_table) {
        lua_log("ioc_table = {");
        lua_inc_level(1);
        asn1p_ioc_table_to_lua(expr->ioc_table);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("tag = {");
    lua_inc_level(1);
    lua_log("tag_value = %ld,", expr->tag.tag_value);
    lua_log("tag_mode = %ld,", expr->tag.tag_mode);
    lua_log("tag_class = %ld,", expr->tag.tag_class);
    lua_inc_level(-1);
    lua_log("},");

    lua_log("marker = {");
    lua_inc_level(1);
    lua_log("flags = %ld,", expr->marker.flags);

    if(expr->marker.default_value) {
        lua_log("default_value = {");
        lua_inc_level(1);
        asn1p_value_to_lua(expr->marker.default_value);
        lua_inc_level(-1);
        lua_log("}");
    }

    lua_inc_level(-1);
    lua_log("},");

    lua_log("unique = %d,", expr->unique);
    lua_log("ref_cnt = %d,", expr->ref_cnt);
    lua_log("auto_tags_OK = %d,", expr->auto_tags_OK);


    if(!TQ_EMPTY(expr, members)) {
        struct asn1p_expr_s *member;
        lua_log("members={");
        lua_inc_level(1);
        TQ_FOR(member, &expr->members, next) {
            lua_log("{");
            lua_inc_level(1);
            asn1p_expr_to_lua(member);
            lua_inc_level(-1);
            lua_log("},");
        }
        lua_inc_level(-1);
        lua_log("},");
    }


    if(expr->parent_expr) {
        lua_log("parent_expr = {");
        lua_inc_level(1);
        asn1p_expr_to_lua(expr->parent_expr);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(expr->module) {
        lua_log("module = {");
        lua_inc_level(1);
        asn1p_module_to_lua(expr->module);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("_lineno = %d,", expr->_lineno);

    return 1;
}
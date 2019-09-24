#include "asn1p_constraint_to_lua.h"
#include "asn1p_globals.h"

int asn1p_constraint_to_lua(struct asn1p_constraint_s *constraint)
{
    if(!constraint)return 0;

    CHECK_RECURSIVE_CALL(constraint);

    lua_log("type = %d,",constraint->type);
    lua_log("presence = %d,",constraint->presence);

    if(constraint->parent_ct)
    {
        lua_log("parent_ct = {");
        lua_inc_level(1);
        asn1p_constraint_to_lua(constraint->parent_ct);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(constraint->containedSubtype)
    {
        lua_log("containedSubtype = {");
        lua_inc_level(1);
        asn1p_value_to_lua(constraint->containedSubtype);
        lua_inc_level(-1);
        lua_log("},");
    }


    if(constraint->value)
    {
        lua_log("value = {");
        lua_inc_level(1);
        asn1p_value_to_lua(constraint->value);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(constraint->range_start)
    {
        lua_log("range_start = {");
        lua_inc_level(1);
        asn1p_value_to_lua(constraint->range_start);
        lua_inc_level(-1);
        lua_log("},");
    }

    if(constraint->range_stop)
    {
        lua_log("range_stop = {");
        lua_inc_level(1);
        asn1p_value_to_lua(constraint->range_stop);
        lua_inc_level(-1);
        lua_log("},");
    }

    lua_log("el_count = %d,",constraint->el_count);
    lua_log("el_size = %d,",constraint->el_size);

    if(constraint->el_count > 0)
    {

        lua_log("elements = {");
        lua_inc_level(1);

        for(int i = 0; i < constraint->el_count; i++)
        {
            lua_log("{");
            lua_inc_level(1);
            asn1p_constraint_to_lua(constraint->elements[i]);
            lua_inc_level(-1);
            lua_log("},");
        }
        lua_inc_level(-1);
        lua_log("},");
    }

    if(constraint->module)
    {
        lua_log("module = {");
        lua_inc_level(1);
        asn1p_module_to_lua(constraint->module);
        lua_inc_level(-1);
        lua_log("},");
    }

    return 1;
}

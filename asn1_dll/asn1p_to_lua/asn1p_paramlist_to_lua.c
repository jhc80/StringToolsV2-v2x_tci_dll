#include "asn1p_paramlist_to_lua.h"
#include "asn1p_ref_to_lua.h"
#include "asn1p_globals.h"

int asn1p_paramlist_to_lua(struct asn1p_paramlist_s *paramlist)
{
    if(!paramlist)return 0;

    CHECK_RECURSIVE_CALL(paramlist);
    
    lua_log("params_count = %d,",paramlist->params_count);
    lua_log("params_size = %d,",paramlist->params_size);
    lua_log("_lineno = %d,",paramlist->_lineno);

    if(paramlist->params)
    {

        lua_log("params={");
        lua_inc_level(1);

        for(int i = 0; i < paramlist->params_count;i++)
        {
            lua_log("{");
            lua_inc_level(1);

            if(paramlist->params[i].governor)
            {
                lua_log("governor = {");
                lua_inc_level(1);
                asn1p_ref_to_lua(paramlist->params[i].governor);
                lua_inc_level(-1);
                lua_log("},");
            }

            if(paramlist->params[i].argument)
            {
                lua_log("argument = \"%s\",",paramlist->params[i].argument);
            }

            lua_inc_level(-1);
            lua_log("}");
        }

        lua_inc_level(-1);
        lua_log("},");
    }


    return 1;
}
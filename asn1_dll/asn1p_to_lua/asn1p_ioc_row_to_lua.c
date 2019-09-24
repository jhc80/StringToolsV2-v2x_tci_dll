#include "asn1p_ioc_row_to_lua.h"
#include "asn1p_globals.h"

int asn1p_ioc_row_to_lua(struct asn1p_ioc_row_s *ioc_row)
{
    if(!ioc_row)return 0;

    CHECK_RECURSIVE_CALL(ioc_row);
    
    lua_log("columns = %d,",ioc_row->columns);

    if(ioc_row->column && ioc_row->columns > 0)
    {
        lua_log("column = {");
        lua_inc_level(1);

        for(int i = 0; i < ioc_row->columns; i++ )
        {
            lua_log("{");
            lua_inc_level(1);
            lua_log("new_ref = %d,",ioc_row->column[i].new_ref);

            if(ioc_row->column[i].value)
            {
                lua_log("value = {");
                lua_inc_level(1);
                asn1p_expr_to_lua(ioc_row->column[i].value);
                lua_inc_level(-1);
                lua_log("},");    
            }    
            
            if(ioc_row->column[i].field)
            {
                lua_log("field = {");
                lua_inc_level(1);
                asn1p_expr_to_lua(ioc_row->column[i].field);
                lua_inc_level(-1);
                lua_log("},");    
            }    

            lua_inc_level(-1);
            lua_log("},");
        }

        lua_inc_level(-1);
        lua_log("},");

    }


    return 1;
}

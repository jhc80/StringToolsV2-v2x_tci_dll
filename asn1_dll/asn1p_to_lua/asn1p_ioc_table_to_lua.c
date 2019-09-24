#include "asn1p_ioc_table_to_lua.h"
#include "asn1p_globals.h"

int asn1p_ioc_table_to_lua(struct asn1p_ioc_table_s *ioc_table)
{
    if(!ioc_table)return 0;

    CHECK_RECURSIVE_CALL(ioc_table);
    
    lua_log("rows = %d,",ioc_table->rows);
    lua_log("extensible = %d,",ioc_table->extensible);

    if(ioc_table->rows > 0 && ioc_table->row)
    {
        lua_log("row = {");
        lua_inc_level(1);

        for(int i = 0; i < ioc_table->rows; i++)
        {
            lua_log("{");
            lua_inc_level(1);
            asn1p_ioc_row_to_lua(ioc_table->row[i]);
            lua_inc_level(-1);
            lua_log("},");
        }

        lua_inc_level(-1);
        lua_log("},");
    }


    return 1;
}

#include "asn1p_to_lua.h"
#include "asn1p_globals.h"
#include "syslog.h"

char* asn1_parse_all_files(const char *filelist[], int list_size, int *ret_len)
{
	globals_init();

	asn1p_t *asn = NULL;
    *ret_len = 0;
    char *ret = NULL;

    for(int i = 0; i < list_size; i++) 
	{
        const char *file = filelist[i];
        asn1p_t *new_asn = asn1p_parse_file(file, A1P_NOFLAGS);

        if(!new_asn) 
		{
            XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
				"error parsing input file %s", file
			);
    	    break;
        }
        // bundle  all modules in one
        if(asn) 
		{
            asn1p_module_t *module;
            while((module = TQ_REMOVE(&new_asn->modules, mod_next))) {
                TQ_ADD(&asn->modules, module, mod_next);
            }
            asn1p_delete(new_asn);
        } 
		else 
		{
            asn = new_asn;
        }
    }

	if(!asn)
	{
		goto out_no_asn;
	}

	if(asn1f_process(asn,0, NULL) < 0)
	{
		XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
			"WARNNING: asn1f_process fail."
		);
	}

	struct asn1p_module_s *module = 0;

	lua_log("{");
	TQ_FOR(module, &asn->modules, mod_next) {
		lua_inc_level(1);
		lua_log("{");
		lua_inc_level(1);
		asn1p_module_to_lua(module);
		lua_inc_level(-1);
		lua_log("},");
		lua_inc_level(-1);
	}
	lua_log("}");

    ret = lua_print_buf_abandon_buf(ret_len);

out_has_asn:
    asn1p_delete(asn);
out_no_asn:	
    asn1p_lex_destroy();
	globals_destroy();
	return ret;
}


char* asn1_parse_string(const void *buf,int buf_size, int *ret_len)
{
	globals_init();
	
    *ret_len = 0;
    char *ret = NULL;

	asn1p_t *asn = asn1p_parse_buffer(buf,buf_size,"<string>",0,A1P_NOFLAGS);

	if(!asn) 
	{
		XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
			"error parsing input buffer"
		);
		goto out_no_asn;
	}

	struct asn1p_module_s *module = 0;

	lua_log("{");
	TQ_FOR(module, &asn->modules, mod_next) {
		lua_inc_level(1);
		lua_log("{");
		lua_inc_level(1);
		asn1p_module_to_lua(module);
		lua_inc_level(-1);
		lua_log("},");
		lua_inc_level(-1);
	}
	lua_log("}");

    ret = lua_print_buf_abandon_buf(ret_len);

    asn1p_delete(asn);
out_no_asn:	
    asn1p_lex_destroy();
	globals_destroy();
	return ret;
}

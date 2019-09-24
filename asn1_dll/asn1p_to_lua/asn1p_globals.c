#include "asn1p_globals.h"
#include "syslog.h"
#include "mem_tool.h"

struct asn1p_obj_map g_asn1p_obj_map;

status_t globals_init(void)
{
    asn1p_obj_map_init(&g_asn1p_obj_map,1024*10);  
    lua_print_buf_init(32*1024*1024);
    return OK;
}

status_t globals_destroy(void)
{  
    lua_print_buf_destroy();
    asn1p_obj_map_destroy(&g_asn1p_obj_map);  
    return OK;
}

static int _obj_id = 1;
static int alloc_obj_id(void)
{
    return _obj_id++;
}

struct asn1p_obj * get_exist_obj(const void *obj)
{
    struct asn1p_obj tmp;
    asn1p_obj_init(&tmp);
    asn1p_obj_set_obj(&tmp,obj);
    struct asn1p_obj *exist = asn1p_obj_map_get(&g_asn1p_obj_map,&tmp);
    asn1p_obj_destroy(&tmp);
    return exist;
}

struct asn1p_obj *add_obj_to_map(const void *obj)
{
    struct asn1p_obj *tmp;

    MALLOC(tmp,struct asn1p_obj,1);

    asn1p_obj_init(tmp);
    asn1p_obj_set_obj(tmp,obj);
    asn1p_obj_set_obj_id(tmp,alloc_obj_id());
    
    if(!asn1p_obj_map_put_ptr(&g_asn1p_obj_map,tmp))
    {
        asn1p_obj_destroy(tmp);
        FREE(tmp);
        return NULL;
    }

    return tmp;
}


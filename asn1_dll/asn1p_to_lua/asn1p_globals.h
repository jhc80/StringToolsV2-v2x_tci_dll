#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "syslog.h"
#include "mem_tool.h"
#include "asn1p_to_lua_common.h"
#include "asn1p_obj_map.h"
#include "to_lua_buf.h"

#include "asn1p_constraint_to_lua.h"
#include "asn1p_ioc_table_to_lua.h"
#include "asn1p_oid_to_lua.h"
#include "asn1p_value_to_lua.h"
#include "asn1p_expr_to_lua.h"
#include "asn1p_module_to_lua.h"
#include "asn1p_paramlist_to_lua.h"
#include "asn1p_wsyntx_chunk_to_lua.h"
#include "asn1p_ref_to_lua.h"
#include "asn1p_wsyntx_to_lua.h"
#include "asn1p_ioc_row_to_lua.h"
#include "asn1p_obj_map.h"
#include "asn1p_xports_to_lua.h"


extern struct asn1p_obj_map g_asn1p_obj_map;

status_t globals_init(void);
status_t globals_destroy(void);

struct asn1p_obj *get_exist_obj(const void *obj);
struct asn1p_obj *add_obj_to_map(const void *obj);

#define TQ_EMPTY(struct_p, member) ((struct_p)->member.tq_head == NULL)

#define CHECK_RECURSIVE_CALL(ptr)                                 \
    do {                                                          \
        struct asn1p_obj *exist = get_exist_obj(ptr);             \
        if(exist) {                                               \
            lua_log("__id__ = %d,", asn1p_obj_get_obj_id(exist)); \
            return 1;                                             \
        }                                                         \
        exist = add_obj_to_map(ptr);                              \
        ASSERT(exist);                                            \
        lua_log("__id__ = %d,", asn1p_obj_get_obj_id(exist));     \
    } while(0)\


#endif

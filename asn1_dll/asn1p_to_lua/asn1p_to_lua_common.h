#ifndef __ASN1P_TO_LUA_COMMON_H
#define __ASN1P_TO_LUA_COMMON_H

#include "asn1_common.h"
#include "asn1fix.h"      /* Fix the ASN.1 tree */
#include "asn1fix_export.h"
#include "asn1parser.h" /* Parse the ASN.1 file and build a tree */

#include "to_lua_buf.h"
#include "asn1p_obj_map.h"

struct asn1p_obj *get_exist_obj(const void *obj);
struct asn1p_obj *add_obj_to_map(const void *obj);

#endif

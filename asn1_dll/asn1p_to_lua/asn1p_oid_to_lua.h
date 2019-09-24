#ifndef __ASN1P_OID_TO_LUA_H
#define __ASN1P_OID_TO_LUA_H

#include "asn1p_to_lua_common.h"

int asn1p_oid_to_lua(struct asn1p_oid_s* oid);
int asn1p_oid_arc_to_lua(struct asn1p_oid_arc_s* oid_arc);

#endif
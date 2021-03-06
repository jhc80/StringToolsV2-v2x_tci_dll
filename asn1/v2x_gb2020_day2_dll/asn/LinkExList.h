/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "asn/Map.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_LinkExList_H_
#define	_LinkExList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct LinkEx;

/* LinkExList */
typedef struct LinkExList {
	A_SEQUENCE_OF(struct LinkEx) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LinkExList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LinkExList;
extern asn_SET_OF_specifics_t asn_SPC_LinkExList_specs_1;
extern asn_TYPE_member_t asn_MBR_LinkExList_1[1];
extern asn_per_constraints_t asn_PER_type_LinkExList_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "LinkEx.h"

#endif	/* _LinkExList_H_ */
#include <asn_internal.h>

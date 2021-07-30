/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "asn/PAM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PAMMovementList_H_
#define	_PAMMovementList_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PAMNodeID.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PAMMovementList */
typedef struct PAMMovementList {
	A_SEQUENCE_OF(PAMNodeID_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PAMMovementList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PAMMovementList;
extern asn_SET_OF_specifics_t asn_SPC_PAMMovementList_specs_1;
extern asn_TYPE_member_t asn_MBR_PAMMovementList_1[1];
extern asn_per_constraints_t asn_PER_type_PAMMovementList_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _PAMMovementList_H_ */
#include <asn_internal.h>

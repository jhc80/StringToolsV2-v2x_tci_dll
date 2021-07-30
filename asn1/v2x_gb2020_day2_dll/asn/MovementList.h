/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "asn/Map.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_MovementList_H_
#define	_MovementList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Movement;

/* MovementList */
typedef struct MovementList {
	A_SEQUENCE_OF(struct Movement) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MovementList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MovementList;
extern asn_SET_OF_specifics_t asn_SPC_MovementList_specs_1;
extern asn_TYPE_member_t asn_MBR_MovementList_1[1];
extern asn_per_constraints_t asn_PER_type_MovementList_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Movement.h"

#endif	/* _MovementList_H_ */
#include <asn_internal.h>

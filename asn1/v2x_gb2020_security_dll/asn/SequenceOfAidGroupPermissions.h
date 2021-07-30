/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityDataTypes"
 * 	found in "asn/SecurityDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SequenceOfAidGroupPermissions_H_
#define	_SequenceOfAidGroupPermissions_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct AidGroupPermissions;

/* SequenceOfAidGroupPermissions */
typedef struct SequenceOfAidGroupPermissions {
	A_SEQUENCE_OF(struct AidGroupPermissions) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfAidGroupPermissions_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfAidGroupPermissions;
extern asn_SET_OF_specifics_t asn_SPC_SequenceOfAidGroupPermissions_specs_1;
extern asn_TYPE_member_t asn_MBR_SequenceOfAidGroupPermissions_1[1];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "AidGroupPermissions.h"

#endif	/* _SequenceOfAidGroupPermissions_H_ */
#include <asn_internal.h>

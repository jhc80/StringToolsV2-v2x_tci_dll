/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CRLBaseTypes"
 * 	found in "asn/CRLBaseTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SequenceOfIndividualRevocation_H_
#define	_SequenceOfIndividualRevocation_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct IndividualRevocation;

/* SequenceOfIndividualRevocation */
typedef struct SequenceOfIndividualRevocation {
	A_SEQUENCE_OF(struct IndividualRevocation) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfIndividualRevocation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfIndividualRevocation;
extern asn_SET_OF_specifics_t asn_SPC_SequenceOfIndividualRevocation_specs_1;
extern asn_TYPE_member_t asn_MBR_SequenceOfIndividualRevocation_1[1];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "IndividualRevocation.h"

#endif	/* _SequenceOfIndividualRevocation_H_ */
#include <asn_internal.h>
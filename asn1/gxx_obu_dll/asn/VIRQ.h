/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_VIRQ_H_
#define	_VIRQ_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BehaviorType.h"
#include "RequestState.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VIRQ */
typedef struct VIRQ {
	BehaviorType_t	 type;
	RequestState_t	 state;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VIRQ_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VIRQ;
extern asn_SEQUENCE_specifics_t asn_SPC_VIRQ_specs_1;
extern asn_TYPE_member_t asn_MBR_VIRQ_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _VIRQ_H_ */
#include <asn_internal.h>

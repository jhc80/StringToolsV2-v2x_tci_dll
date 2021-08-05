/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaRaInterfacePdu"
 * 	found in "asn/LaRaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_LaPraLinkageValueResponse_H_
#define	_LaPraLinkageValueResponse_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint16.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct IndividualLVResponseLinkageChain;
struct GroupLVResponseLinkageChain;

/* LaPraLinkageValueResponse */
typedef struct LaPraLinkageValueResponse {
	Uint16_t	 iMin;
	Uint16_t	 iMax;
	struct LaPraLinkageValueResponse__individualLVs {
		A_SEQUENCE_OF(struct IndividualLVResponseLinkageChain) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} individualLVs;
	struct LaPraLinkageValueResponse__groupLVs {
		A_SEQUENCE_OF(struct GroupLVResponseLinkageChain) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} groupLVs;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LaPraLinkageValueResponse_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LaPraLinkageValueResponse;
extern asn_SEQUENCE_specifics_t asn_SPC_LaPraLinkageValueResponse_specs_1;
extern asn_TYPE_member_t asn_MBR_LaPraLinkageValueResponse_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "IndividualLVResponseLinkageChain.h"
#include "GroupLVResponseLinkageChain.h"

#endif	/* _LaPraLinkageValueResponse_H_ */
#include <asn_internal.h>
/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_RxSpatRequirement_H_
#define	_RxSpatRequirement_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PhaseID.h"
#include "ParamInSpat.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RxSpatRequirement */
typedef struct RxSpatRequirement {
	PhaseID_t	*phaseId	/* OPTIONAL */;
	ParamInSpat_t	 paramInSpat;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RxSpatRequirement_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RxSpatRequirement;
extern asn_SEQUENCE_specifics_t asn_SPC_RxSpatRequirement_specs_1;
extern asn_TYPE_member_t asn_MBR_RxSpatRequirement_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _RxSpatRequirement_H_ */
#include <asn_internal.h>
/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_RxPduParamFlag_H_
#define	_RxPduParamFlag_H_


#include <asn_application.h>

/* Including external dependencies */
#include "BsmPduParam.h"
#include "RxMapRequirement.h"
#include "RxSpatRequirement.h"
#include "RxRsiRequirement.h"
#include "RxRsmRequirement.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum RxPduParamFlag_PR {
	RxPduParamFlag_PR_NOTHING,	/* No components present */
	RxPduParamFlag_PR_rxBsmPduParam,
	RxPduParamFlag_PR_rxMapRequirement,
	RxPduParamFlag_PR_rxSpatRequirement,
	RxPduParamFlag_PR_rxRsiRequirement,
	RxPduParamFlag_PR_rxRsmRequirement
	/* Extensions may appear below */
	
} RxPduParamFlag_PR;

/* RxPduParamFlag */
typedef struct RxPduParamFlag {
	RxPduParamFlag_PR present;
	union RxPduParamFlag_u {
		BsmPduParam_t	 rxBsmPduParam;
		RxMapRequirement_t	 rxMapRequirement;
		RxSpatRequirement_t	 rxSpatRequirement;
		RxRsiRequirement_t	 rxRsiRequirement;
		RxRsmRequirement_t	 rxRsmRequirement;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RxPduParamFlag_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RxPduParamFlag;
extern asn_CHOICE_specifics_t asn_SPC_RxPduParamFlag_specs_1;
extern asn_TYPE_member_t asn_MBR_RxPduParamFlag_1[5];
extern asn_per_constraints_t asn_PER_type_RxPduParamFlag_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _RxPduParamFlag_H_ */
#include <asn_internal.h>

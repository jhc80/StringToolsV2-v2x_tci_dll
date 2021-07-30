/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaMaInterfacePdu"
 * 	found in "asn/LaMaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_LaMaInterfacePdu_H_
#define	_LaMaInterfacePdu_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MaLaLinkageSeedRequest.h"
#include "LaMaLinkageSeedResponse.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LaMaInterfacePdu_PR {
	LaMaInterfacePdu_PR_NOTHING,	/* No components present */
	LaMaInterfacePdu_PR_maLaLinkageSeedRequest,
	LaMaInterfacePdu_PR_laMaLinkageSeedResponse
	/* Extensions may appear below */
	
} LaMaInterfacePdu_PR;

/* LaMaInterfacePdu */
typedef struct LaMaInterfacePdu {
	LaMaInterfacePdu_PR present;
	union LaMaInterfacePdu_u {
		MaLaLinkageSeedRequest_t	 maLaLinkageSeedRequest;
		LaMaLinkageSeedResponse_t	 laMaLinkageSeedResponse;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LaMaInterfacePdu_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LaMaInterfacePdu;
extern asn_CHOICE_specifics_t asn_SPC_LaMaInterfacePdu_specs_1;
extern asn_TYPE_member_t asn_MBR_LaMaInterfacePdu_1[2];
extern asn_per_constraints_t asn_PER_type_LaMaInterfacePdu_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _LaMaInterfacePdu_H_ */
#include <asn_internal.h>

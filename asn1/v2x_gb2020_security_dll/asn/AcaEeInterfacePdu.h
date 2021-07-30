/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AcaEeInterfacePdu"
 * 	found in "asn/AcaEeInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_AcaEeInterfacePdu_H_
#define	_AcaEeInterfacePdu_H_


#include <asn_application.h>

/* Including external dependencies */
#include "AcaEeCertResponse.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum AcaEeInterfacePdu_PR {
	AcaEeInterfacePdu_PR_NOTHING,	/* No components present */
	AcaEeInterfacePdu_PR_acaEeCertResponse
	/* Extensions may appear below */
	
} AcaEeInterfacePdu_PR;

/* AcaEeInterfacePdu */
typedef struct AcaEeInterfacePdu {
	AcaEeInterfacePdu_PR present;
	union AcaEeInterfacePdu_u {
		AcaEeCertResponse_t	 acaEeCertResponse;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AcaEeInterfacePdu_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AcaEeInterfacePdu;
extern asn_CHOICE_specifics_t asn_SPC_AcaEeInterfacePdu_specs_1;
extern asn_TYPE_member_t asn_MBR_AcaEeInterfacePdu_1[1];
extern asn_per_constraints_t asn_PER_type_AcaEeInterfacePdu_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _AcaEeInterfacePdu_H_ */
#include <asn_internal.h>

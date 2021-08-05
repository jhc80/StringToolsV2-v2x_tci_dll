/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ECDHContent_H_
#define	_ECDHContent_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ECDHData.h"
#include "ECDHConfirm.h"
#include "ECDHResult.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ECDHContent_PR {
	ECDHContent_PR_NOTHING,	/* No components present */
	ECDHContent_PR_exchangeData,
	ECDHContent_PR_exchangeConfirm,
	ECDHContent_PR_exchangeResult
	/* Extensions may appear below */
	
} ECDHContent_PR;

/* ECDHContent */
typedef struct ECDHContent {
	ECDHContent_PR present;
	union ECDHContent_u {
		ECDHData_t	 exchangeData;
		ECDHConfirm_t	 exchangeConfirm;
		ECDHResult_t	 exchangeResult;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ECDHContent_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ECDHContent;
extern asn_CHOICE_specifics_t asn_SPC_ECDHContent_specs_1;
extern asn_TYPE_member_t asn_MBR_ECDHContent_1[3];
extern asn_per_constraints_t asn_PER_type_ECDHContent_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _ECDHContent_H_ */
#include <asn_internal.h>
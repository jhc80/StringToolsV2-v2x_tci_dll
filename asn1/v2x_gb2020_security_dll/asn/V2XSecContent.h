/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityDataTypes"
 * 	found in "asn/SecurityDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_V2XSecContent_H_
#define	_V2XSecContent_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Opaque.h"
#include "EncryptedData.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum V2XSecContent_PR {
	V2XSecContent_PR_NOTHING,	/* No components present */
	V2XSecContent_PR_unsecuredData,
	V2XSecContent_PR_signedData,
	V2XSecContent_PR_encryptedData,
	V2XSecContent_PR_signedCertificateRequest
	/* Extensions may appear below */
	
} V2XSecContent_PR;

/* Forward declarations */
struct SignedData;

/* V2XSecContent */
typedef struct V2XSecContent {
	V2XSecContent_PR present;
	union V2XSecContent_u {
		Opaque_t	 unsecuredData;
		struct SignedData	*signedData;
		EncryptedData_t	 encryptedData;
		Opaque_t	 signedCertificateRequest;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} V2XSecContent_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_V2XSecContent;
extern asn_CHOICE_specifics_t asn_SPC_V2XSecContent_specs_1;
extern asn_TYPE_member_t asn_MBR_V2XSecContent_1[4];
extern asn_per_constraints_t asn_PER_type_V2XSecContent_constr_1;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SignedData.h"

#endif	/* _V2XSecContent_H_ */
#include <asn_internal.h>
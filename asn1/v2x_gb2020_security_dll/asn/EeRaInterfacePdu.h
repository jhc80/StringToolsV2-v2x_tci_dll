/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "EeRaInterfacePdu"
 * 	found in "asn/EeRaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_EeRaInterfacePdu_H_
#define	_EeRaInterfacePdu_H_


#include <asn_application.h>

/* Including external dependencies */
#include "EeRaCertRequest.h"
#include "RaEeCertAck.h"
#include "RaEeCertInfo.h"
#include "EeRaDownloadRequest.h"
#include "EeEcaCertRequestSpdu.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum EeRaInterfacePdu_PR {
	EeRaInterfacePdu_PR_NOTHING,	/* No components present */
	EeRaInterfacePdu_PR_eeRaCertRequest,
	EeRaInterfacePdu_PR_raEeCertAck,
	EeRaInterfacePdu_PR_raEeCertInfo,
	EeRaInterfacePdu_PR_eeRaDownloadRequest,
	EeRaInterfacePdu_PR_eeRaSuccessorEnrollmentCertRequest
	/* Extensions may appear below */
	
} EeRaInterfacePdu_PR;

/* EeRaInterfacePdu */
typedef struct EeRaInterfacePdu {
	EeRaInterfacePdu_PR present;
	union EeRaInterfacePdu_u {
		EeRaCertRequest_t	 eeRaCertRequest;
		RaEeCertAck_t	 raEeCertAck;
		RaEeCertInfo_t	 raEeCertInfo;
		EeRaDownloadRequest_t	 eeRaDownloadRequest;
		EeEcaCertRequestSpdu_t	 eeRaSuccessorEnrollmentCertRequest;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EeRaInterfacePdu_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EeRaInterfacePdu;
extern asn_CHOICE_specifics_t asn_SPC_EeRaInterfacePdu_specs_1;
extern asn_TYPE_member_t asn_MBR_EeRaInterfacePdu_1[5];
extern asn_per_constraints_t asn_PER_type_EeRaInterfacePdu_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _EeRaInterfacePdu_H_ */
#include <asn_internal.h>

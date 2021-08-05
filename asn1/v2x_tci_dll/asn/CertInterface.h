/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_CertInterface_H_
#define	_CertInterface_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SendCertReq.h"
#include "CertRequest.h"
#include "CertAck.h"
#include "CertDownload.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CertInterface_PR {
	CertInterface_PR_NOTHING,	/* No components present */
	CertInterface_PR_sendCertReq,
	CertInterface_PR_certRequest,
	CertInterface_PR_certAck,
	CertInterface_PR_certDownload
	/* Extensions may appear below */
	
} CertInterface_PR;

/* CertInterface */
typedef struct CertInterface {
	CertInterface_PR present;
	union CertInterface_u {
		SendCertReq_t	 sendCertReq;
		CertRequest_t	 certRequest;
		CertAck_t	 certAck;
		CertDownload_t	 certDownload;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CertInterface_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CertInterface;
extern asn_CHOICE_specifics_t asn_SPC_CertInterface_specs_1;
extern asn_TYPE_member_t asn_MBR_CertInterface_1[4];
extern asn_per_constraints_t asn_PER_type_CertInterface_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _CertInterface_H_ */
#include <asn_internal.h>
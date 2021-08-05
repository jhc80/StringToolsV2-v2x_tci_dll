/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "EeRaInterfacePdu"
 * 	found in "asn/EeRaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_EeRaDownloadRequest_H_
#define	_EeRaDownloadRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Time32.h"
#include <UTF8String.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* EeRaDownloadRequest */
typedef struct EeRaDownloadRequest {
	Time32_t	 generationTime;
	UTF8String_t	 filename;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} EeRaDownloadRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EeRaDownloadRequest;
extern asn_SEQUENCE_specifics_t asn_SPC_EeRaDownloadRequest_specs_1;
extern asn_TYPE_member_t asn_MBR_EeRaDownloadRequest_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _EeRaDownloadRequest_H_ */
#include <asn_internal.h>
/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_CertRequest_H_
#define	_CertRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint8.h"
#include "Time32.h"
#include "TbsCert.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PublicEncryptionKey;

/* CertRequest */
typedef struct CertRequest {
	Uint8_t	 version;
	Time32_t	 currentTime;
	TbsCert_t	 tbsCertData;
	struct PublicEncryptionKey	*encryptionKey	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CertRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CertRequest;
extern asn_SEQUENCE_specifics_t asn_SPC_CertRequest_specs_1;
extern asn_TYPE_member_t asn_MBR_CertRequest_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PublicEncryptionKey.h"

#endif	/* _CertRequest_H_ */
#include <asn_internal.h>

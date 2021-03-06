/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_CertificateDigest_H_
#define	_CertificateDigest_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HashAlgorithm.h"
#include "HashedId8.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CertificateDigest */
typedef struct CertificateDigest {
	HashAlgorithm_t	 algorithm;
	HashedId8_t	 digest;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} CertificateDigest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_CertificateDigest;
extern asn_SEQUENCE_specifics_t asn_SPC_CertificateDigest_specs_1;
extern asn_TYPE_member_t asn_MBR_CertificateDigest_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _CertificateDigest_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_AesCcmCipherText_H_
#define	_AesCcmCipherText_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include "CipherText.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* AesCcmCipherText */
typedef struct AesCcmCipherText {
	OCTET_STRING_t	 nonce;
	CipherText_t	 cipher;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AesCcmCipherText_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AesCcmCipherText;
extern asn_SEQUENCE_specifics_t asn_SPC_AesCcmCipherText_specs_1;
extern asn_TYPE_member_t asn_MBR_AesCcmCipherText_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _AesCcmCipherText_H_ */
#include <asn_internal.h>

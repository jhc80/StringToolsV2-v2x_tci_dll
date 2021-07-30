/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PublicEncryptionKey_H_
#define	_PublicEncryptionKey_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SymmetricAlgorithm.h"
#include "EccCurve.h"
#include "ECCPoint.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PublicEncryptionKey */
typedef struct PublicEncryptionKey {
	SymmetricAlgorithm_t	 supportedSymmAlg;
	EccCurve_t	 eccCurve;
	ECCPoint_t	 publicKey;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PublicEncryptionKey_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PublicEncryptionKey;
extern asn_SEQUENCE_specifics_t asn_SPC_PublicEncryptionKey_specs_1;
extern asn_TYPE_member_t asn_MBR_PublicEncryptionKey_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _PublicEncryptionKey_H_ */
#include <asn_internal.h>

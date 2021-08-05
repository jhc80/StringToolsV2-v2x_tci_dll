/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Signature_H_
#define	_Signature_H_


#include <asn_application.h>

/* Including external dependencies */
#include "EccCurve.h"
#include "ECCPoint.h"
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Signature */
typedef struct Signature {
	EccCurve_t	 curve;
	ECCPoint_t	 r;
	OCTET_STRING_t	 s;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Signature_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Signature;
extern asn_SEQUENCE_specifics_t asn_SPC_Signature_specs_1;
extern asn_TYPE_member_t asn_MBR_Signature_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _Signature_H_ */
#include <asn_internal.h>
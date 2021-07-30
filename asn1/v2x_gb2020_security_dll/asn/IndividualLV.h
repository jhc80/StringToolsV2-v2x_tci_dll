/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaMaInterfacePdu"
 * 	found in "asn/LaMaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_IndividualLV_H_
#define	_IndividualLV_H_


#include <asn_application.h>

/* Including external dependencies */
#include "IValue.h"
#include "LinkageValue.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* IndividualLV */
typedef struct IndividualLV {
	IValue_t	 iValue;
	LinkageValue_t	 lv;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IndividualLV_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IndividualLV;
extern asn_SEQUENCE_specifics_t asn_SPC_IndividualLV_specs_1;
extern asn_TYPE_member_t asn_MBR_IndividualLV_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _IndividualLV_H_ */
#include <asn_internal.h>

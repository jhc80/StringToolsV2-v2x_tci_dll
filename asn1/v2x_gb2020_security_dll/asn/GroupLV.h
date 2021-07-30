/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaMaInterfacePdu"
 * 	found in "asn/LaMaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_GroupLV_H_
#define	_GroupLV_H_


#include <asn_application.h>

/* Including external dependencies */
#include "IValue.h"
#include "Uint32.h"
#include "LinkageValue.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GroupLV */
typedef struct GroupLV {
	IValue_t	 iValue;
	Uint32_t	 j;
	LinkageValue_t	 lv;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GroupLV_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GroupLV;
extern asn_SEQUENCE_specifics_t asn_SPC_GroupLV_specs_1;
extern asn_TYPE_member_t asn_MBR_GroupLV_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _GroupLV_H_ */
#include <asn_internal.h>

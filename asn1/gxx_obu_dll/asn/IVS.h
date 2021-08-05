/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_IVS_H_
#define	_IVS_H_


#include <asn_application.h>

/* Including external dependencies */
#include "WarnState.h"
#include "SignType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* IVS */
typedef struct IVS {
	WarnState_t	 warnState;
	SignType_t	 signType;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} IVS_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_IVS;
extern asn_SEQUENCE_specifics_t asn_SPC_IVS_specs_1;
extern asn_TYPE_member_t asn_MBR_IVS_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _IVS_H_ */
#include <asn_internal.h>
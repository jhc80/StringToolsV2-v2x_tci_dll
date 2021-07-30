/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TJW_H_
#define	_TJW_H_


#include <asn_application.h>

/* Including external dependencies */
#include "WarnState.h"
#include "TJLevel.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TJW */
typedef struct TJW {
	WarnState_t	 warnState;
	TJLevel_t	 tjLevel;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TJW_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TJW;
extern asn_SEQUENCE_specifics_t asn_SPC_TJW_specs_1;
extern asn_TYPE_member_t asn_MBR_TJW_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _TJW_H_ */
#include <asn_internal.h>

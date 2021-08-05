/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ACK_H_
#define	_ACK_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ErrorCode.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ACK */
typedef struct ACK {
	ErrorCode_t	 errorCode;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ACK_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ACK;
extern asn_SEQUENCE_specifics_t asn_SPC_ACK_specs_1;
extern asn_TYPE_member_t asn_MBR_ACK_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _ACK_H_ */
#include <asn_internal.h>
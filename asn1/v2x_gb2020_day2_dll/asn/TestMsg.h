/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TestMsg"
 * 	found in "asn/TestMsg.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TestMsg_H_
#define	_TestMsg_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MsgCount.h"
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TestMsg */
typedef struct TestMsg {
	MsgCount_t	 msgCnt;
	OCTET_STRING_t	 userData;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TestMsg_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TestMsg;
extern asn_SEQUENCE_specifics_t asn_SPC_TestMsg_specs_1;
extern asn_TYPE_member_t asn_MBR_TestMsg_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _TestMsg_H_ */
#include <asn_internal.h>
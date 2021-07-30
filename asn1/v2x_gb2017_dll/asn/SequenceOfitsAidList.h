/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SequenceOfitsAidList_H_
#define	_SequenceOfitsAidList_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ItsAid.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SequenceOfitsAidList */
typedef struct SequenceOfitsAidList {
	A_SEQUENCE_OF(ItsAid_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SequenceOfitsAidList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SequenceOfitsAidList;
extern asn_SET_OF_specifics_t asn_SPC_SequenceOfitsAidList_specs_1;
extern asn_TYPE_member_t asn_MBR_SequenceOfitsAidList_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _SequenceOfitsAidList_H_ */
#include <asn_internal.h>

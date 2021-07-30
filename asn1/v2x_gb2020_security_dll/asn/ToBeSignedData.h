/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityDataTypes"
 * 	found in "asn/SecurityDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ToBeSignedData_H_
#define	_ToBeSignedData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HeaderInfo.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SignedDataPayload;

/* ToBeSignedData */
typedef struct ToBeSignedData {
	struct SignedDataPayload	*payload;
	HeaderInfo_t	 headerInfo;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ToBeSignedData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ToBeSignedData;
extern asn_SEQUENCE_specifics_t asn_SPC_ToBeSignedData_specs_1;
extern asn_TYPE_member_t asn_MBR_ToBeSignedData_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SignedDataPayload.h"

#endif	/* _ToBeSignedData_H_ */
#include <asn_internal.h>

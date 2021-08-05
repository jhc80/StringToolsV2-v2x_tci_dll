/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityDataTypes"
 * 	found in "asn/SecurityDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_V2XSecData_H_
#define	_V2XSecData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint8.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct V2XSecContent;

/* V2XSecData */
typedef struct V2XSecData {
	Uint8_t	 protocolVersion;
	struct V2XSecContent	*content;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} V2XSecData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_V2XSecData;
extern asn_SEQUENCE_specifics_t asn_SPC_V2XSecData_specs_1;
extern asn_TYPE_member_t asn_MBR_V2XSecData_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "V2XSecContent.h"

#endif	/* _V2XSecData_H_ */
#include <asn_internal.h>
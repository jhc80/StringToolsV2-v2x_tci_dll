/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_OBUInfo_H_
#define	_OBUInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "OBUType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct OBUMotionStatus;

/* OBUInfo */
typedef struct OBUInfo {
	OBUType_t	 obuType;
	struct OBUMotionStatus	*obuMotionStatus	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} OBUInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_OBUInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_OBUInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_OBUInfo_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "OBUMotionStatus.h"

#endif	/* _OBUInfo_H_ */
#include <asn_internal.h>

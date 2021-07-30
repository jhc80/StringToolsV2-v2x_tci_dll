/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PtcData_H_
#define	_PtcData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PtcType.h"
#include <NativeInteger.h>
#include "SourceType.h"
#include <OCTET_STRING.h>
#include "DSecond.h"
#include "PositionOffsetLLV.h"
#include "PositionConfidenceSet.h"
#include "VehSpeed.h"
#include "VehHeading.h"
#include "VehSize.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PtcData */
typedef struct PtcData {
	PtcType_t	 ptcType;
	long	 ptcId;
	SourceType_t	 source;
	OCTET_STRING_t	*id	/* OPTIONAL */;
	DSecond_t	 secMark;
	PositionOffsetLLV_t	 pos;
	PositionConfidenceSet_t	 posConfidence;
	VehSpeed_t	 speed;
	VehHeading_t	 heading;
	VehSize_t	 size;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PtcData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PtcData;
extern asn_SEQUENCE_specifics_t asn_SPC_PtcData_specs_1;
extern asn_TYPE_member_t asn_MBR_PtcData_1[10];

#ifdef __cplusplus
}
#endif

#endif	/* _PtcData_H_ */
#include <asn_internal.h>

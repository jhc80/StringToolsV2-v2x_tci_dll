/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "asn/VIR.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Req_ClearTheWay_H_
#define	_Req_ClearTheWay_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NodeReferenceID.h"
#include "LaneID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ReferencePath;
struct DDateTime;

/* Req-ClearTheWay */
typedef struct Req_ClearTheWay {
	NodeReferenceID_t	 upstreamNode;
	NodeReferenceID_t	 downstreamNode;
	LaneID_t	 targetLane;
	struct ReferencePath	*relatedPath	/* OPTIONAL */;
	struct DDateTime	*tBegin	/* OPTIONAL */;
	struct DDateTime	*tEnd	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Req_ClearTheWay_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Req_ClearTheWay;
extern asn_SEQUENCE_specifics_t asn_SPC_Req_ClearTheWay_specs_1;
extern asn_TYPE_member_t asn_MBR_Req_ClearTheWay_1[6];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ReferencePath.h"
#include "DDateTime.h"

#endif	/* _Req_ClearTheWay_H_ */
#include <asn_internal.h>
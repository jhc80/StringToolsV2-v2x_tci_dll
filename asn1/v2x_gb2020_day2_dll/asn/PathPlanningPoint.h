/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "asn/VIR.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PathPlanningPoint_H_
#define	_PathPlanningPoint_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PositionOffsetLLV.h"
#include "Speed.h"
#include "SpeedConfidence.h"
#include "Heading.h"
#include "HeadingConfidence.h"
#include "TimeOffset.h"
#include "Confidence.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ReferenceLink;
struct PositionConfidenceSet;
struct AccelerationSet4Way;
struct AccSet4WayConfidence;

/* PathPlanningPoint */
typedef struct PathPlanningPoint {
	struct ReferenceLink	*posInMap	/* OPTIONAL */;
	PositionOffsetLLV_t	 pos;
	struct PositionConfidenceSet	*posAccuracy	/* OPTIONAL */;
	Speed_t	*speed	/* OPTIONAL */;
	SpeedConfidence_t	*speedCfd	/* OPTIONAL */;
	Heading_t	*heading	/* OPTIONAL */;
	HeadingConfidence_t	*headingCfd	/* OPTIONAL */;
	struct AccelerationSet4Way	*accelSet	/* OPTIONAL */;
	struct AccSet4WayConfidence	*acc4WayConfidence	/* OPTIONAL */;
	TimeOffset_t	*estimatedTime	/* OPTIONAL */;
	Confidence_t	*timeConfidence	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PathPlanningPoint_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PathPlanningPoint;
extern asn_SEQUENCE_specifics_t asn_SPC_PathPlanningPoint_specs_1;
extern asn_TYPE_member_t asn_MBR_PathPlanningPoint_1[11];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ReferenceLink.h"
#include "PositionConfidenceSet.h"
#include "AccelerationSet4Way.h"
#include "AccSet4WayConfidence.h"

#endif	/* _PathPlanningPoint_H_ */
#include <asn_internal.h>

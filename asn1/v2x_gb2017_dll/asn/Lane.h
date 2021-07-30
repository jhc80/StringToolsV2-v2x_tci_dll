/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MapLane"
 * 	found in "asn/MapLane.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Lane_H_
#define	_Lane_H_


#include <asn_application.h>

/* Including external dependencies */
#include "LaneID.h"
#include "AllowedManeuvers.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct LaneAttributes;
struct ConnectsToList;
struct SpeedLimitList;
struct PointList;

/* Lane */
typedef struct Lane {
	LaneID_t	 laneID;
	struct LaneAttributes	*laneAttributes	/* OPTIONAL */;
	AllowedManeuvers_t	*maneuvers	/* OPTIONAL */;
	struct ConnectsToList	*connectsTo	/* OPTIONAL */;
	struct SpeedLimitList	*speedLimits	/* OPTIONAL */;
	struct PointList	*points	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Lane_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Lane;
extern asn_SEQUENCE_specifics_t asn_SPC_Lane_specs_1;
extern asn_TYPE_member_t asn_MBR_Lane_1[6];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "LaneAttributes.h"
#include "ConnectsToList.h"
#include "SpeedLimitList.h"
#include "PointList.h"

#endif	/* _Lane_H_ */
#include <asn_internal.h>

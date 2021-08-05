/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "asn/PAM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PAMDrive_H_
#define	_PAMDrive_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PAMNodeID.h"
#include <NativeInteger.h>
#include <BOOLEAN.h>
#include "Speed.h"
#include "LaneWidth.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PointList;
struct PAMMovementList;
struct ParkingSlots;

/* PAMDrive */
typedef struct PAMDrive {
	PAMNodeID_t	 upstreamPAMNodeId;
	long	*driveID	/* OPTIONAL */;
	BOOLEAN_t	*twowaySepration	/* OPTIONAL */;
	Speed_t	*speedLimit	/* OPTIONAL */;
	long	*heightRestriction	/* OPTIONAL */;
	LaneWidth_t	*driveWidth	/* OPTIONAL */;
	long	*laneNum	/* OPTIONAL */;
	struct PointList	*points	/* OPTIONAL */;
	struct PAMMovementList	*movements	/* OPTIONAL */;
	struct ParkingSlots	*parkingSlots	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PAMDrive_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PAMDrive;
extern asn_SEQUENCE_specifics_t asn_SPC_PAMDrive_specs_1;
extern asn_TYPE_member_t asn_MBR_PAMDrive_1[10];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PointList.h"
#include "PAMMovementList.h"
#include "ParkingSlots.h"

#endif	/* _PAMDrive_H_ */
#include <asn_internal.h>
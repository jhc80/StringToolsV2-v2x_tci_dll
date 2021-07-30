/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VehSafetyExt"
 * 	found in "asn/VehSafetyExt.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_VehicleSafetyExtensions_H_
#define	_VehicleSafetyExtensions_H_


#include <asn_application.h>

/* Including external dependencies */
#include "VehicleEventFlags.h"
#include "ExteriorLights.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PathHistory;
struct PathPrediction;

/* VehicleSafetyExtensions */
typedef struct VehicleSafetyExtensions {
	VehicleEventFlags_t	*events	/* OPTIONAL */;
	struct PathHistory	*pathHistory	/* OPTIONAL */;
	struct PathPrediction	*pathPrediction	/* OPTIONAL */;
	ExteriorLights_t	*lights	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehicleSafetyExtensions_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehicleSafetyExtensions;
extern asn_SEQUENCE_specifics_t asn_SPC_VehicleSafetyExtensions_specs_1;
extern asn_TYPE_member_t asn_MBR_VehicleSafetyExtensions_1[4];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PathHistory.h"
#include "PathPrediction.h"

#endif	/* _VehicleSafetyExtensions_H_ */
#include <asn_internal.h>

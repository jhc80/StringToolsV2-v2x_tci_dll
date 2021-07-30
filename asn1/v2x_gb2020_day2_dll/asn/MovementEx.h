/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "asn/Map.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_MovementEx_H_
#define	_MovementEx_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NodeReferenceID.h"
#include "PhaseID.h"
#include "Maneuver.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MovementEx */
typedef struct MovementEx {
	NodeReferenceID_t	 remoteIntersection;
	PhaseID_t	*phaseId	/* OPTIONAL */;
	Maneuver_t	*turn_direction	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MovementEx_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MovementEx;
extern asn_SEQUENCE_specifics_t asn_SPC_MovementEx_specs_1;
extern asn_TYPE_member_t asn_MBR_MovementEx_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _MovementEx_H_ */
#include <asn_internal.h>

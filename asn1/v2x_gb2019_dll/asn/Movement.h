/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MapLink"
 * 	found in "asn/MapLink.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Movement_H_
#define	_Movement_H_


#include <asn_application.h>

/* Including external dependencies */
#include "NodeReferenceID.h"
#include "PhaseID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Movement */
typedef struct Movement {
	NodeReferenceID_t	 remoteIntersection;
	PhaseID_t	*phaseId	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Movement_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Movement;
extern asn_SEQUENCE_specifics_t asn_SPC_Movement_specs_1;
extern asn_TYPE_member_t asn_MBR_Movement_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _Movement_H_ */
#include <asn_internal.h>

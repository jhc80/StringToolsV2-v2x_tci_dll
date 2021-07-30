/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MapNode"
 * 	found in "asn/MapNode.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_NodeReferenceID_H_
#define	_NodeReferenceID_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RoadRegulatorID.h"
#include "NodeID.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NodeReferenceID */
typedef struct NodeReferenceID {
	RoadRegulatorID_t	*region	/* OPTIONAL */;
	NodeID_t	 id;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NodeReferenceID_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NodeReferenceID;
extern asn_SEQUENCE_specifics_t asn_SPC_NodeReferenceID_specs_1;
extern asn_TYPE_member_t asn_MBR_NodeReferenceID_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _NodeReferenceID_H_ */
#include <asn_internal.h>

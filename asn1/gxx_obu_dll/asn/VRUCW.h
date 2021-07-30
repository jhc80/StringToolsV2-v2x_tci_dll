/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_VRUCW_H_
#define	_VRUCW_H_


#include <asn_application.h>

/* Including external dependencies */
#include "WarnState.h"
#include "Distance.h"
#include "Direction.h"
#include "ParticipantInfo.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VRUCW */
typedef struct VRUCW {
	WarnState_t	 warnState;
	Distance_t	 distance;
	Direction_t	 direction;
	ParticipantInfo_t	 participant;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VRUCW_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VRUCW;
extern asn_SEQUENCE_specifics_t asn_SPC_VRUCW_specs_1;
extern asn_TYPE_member_t asn_MBR_VRUCW_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _VRUCW_H_ */
#include <asn_internal.h>

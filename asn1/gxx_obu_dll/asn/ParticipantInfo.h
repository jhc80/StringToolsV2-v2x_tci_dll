/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ParticipantInfo_H_
#define	_ParticipantInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Position3D.h"
#include "Speed.h"
#include "Heading.h"
#include "VehicleSize.h"
#include "VehicleType.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ParticipantInfo */
typedef struct ParticipantInfo {
	Position3D_t	 pos;
	Speed_t	 speed;
	Heading_t	 heading;
	VehicleSize_t	 size;
	VehicleType_t	 type;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ParticipantInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ParticipantInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_ParticipantInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_ParticipantInfo_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _ParticipantInfo_H_ */
#include <asn_internal.h>

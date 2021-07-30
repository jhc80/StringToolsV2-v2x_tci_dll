/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PSM"
 * 	found in "asn/PSM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Non_motorData_H_
#define	_Non_motorData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PersonalDeviceUserType.h"
#include "NumberOfParticipantsInCluster.h"
#include "Attachment.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PropelledInformation;
struct PersonalExtensions;
struct RoadWorkerExtensions;
struct PersonalRequest;

/* Non-motorData */
typedef struct Non_motorData {
	PersonalDeviceUserType_t	 basicType;
	struct PropelledInformation	*propulsion	/* OPTIONAL */;
	NumberOfParticipantsInCluster_t	*clusterSize	/* OPTIONAL */;
	Attachment_t	*attachment	/* OPTIONAL */;
	struct PersonalExtensions	*personalExt	/* OPTIONAL */;
	struct RoadWorkerExtensions	*roadWorkerExt	/* OPTIONAL */;
	struct PersonalRequest	*personalReq	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Non_motorData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Non_motorData;
extern asn_SEQUENCE_specifics_t asn_SPC_Non_motorData_specs_1;
extern asn_TYPE_member_t asn_MBR_Non_motorData_1[7];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PropelledInformation.h"
#include "PersonalExtensions.h"
#include "RoadWorkerExtensions.h"
#include "PersonalRequest.h"

#endif	/* _Non_motorData_H_ */
#include <asn_internal.h>

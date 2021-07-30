/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VIR"
 * 	found in "asn/VIR.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_DriveRequest_H_
#define	_DriveRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "ReqStatus.h"
#include <OCTET_STRING.h>
#include "TimeOffset.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ReqInfo;

/* DriveRequest */
typedef struct DriveRequest {
	long	 reqID;
	ReqStatus_t	 status;
	OCTET_STRING_t	*reqPriority	/* OPTIONAL */;
	OCTET_STRING_t	*targetVeh	/* OPTIONAL */;
	OCTET_STRING_t	*targetRSU	/* OPTIONAL */;
	struct ReqInfo	*info	/* OPTIONAL */;
	TimeOffset_t	*lifeTime	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} DriveRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_DriveRequest;
extern asn_SEQUENCE_specifics_t asn_SPC_DriveRequest_specs_1;
extern asn_TYPE_member_t asn_MBR_DriveRequest_1[7];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ReqInfo.h"

#endif	/* _DriveRequest_H_ */
#include <asn_internal.h>

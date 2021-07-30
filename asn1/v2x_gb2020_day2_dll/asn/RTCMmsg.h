/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RTCM"
 * 	found in "asn/RTCM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_RTCMmsg_H_
#define	_RTCMmsg_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RTCM-Revision.h"
#include "RTCM-ID.h"
#include "RTCM-Payload.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RTCMmsg */
typedef struct RTCMmsg {
	RTCM_Revision_t	*rev	/* OPTIONAL */;
	RTCM_ID_t	*rtcmID	/* OPTIONAL */;
	RTCM_Payload_t	 payload;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RTCMmsg_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RTCMmsg;
extern asn_SEQUENCE_specifics_t asn_SPC_RTCMmsg_specs_1;
extern asn_TYPE_member_t asn_MBR_RTCMmsg_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _RTCMmsg_H_ */
#include <asn_internal.h>

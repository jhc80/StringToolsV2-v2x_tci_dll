/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MsgDayII"
 * 	found in "asn/MsgDayII.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_MessageFrameExt_H_
#define	_MessageFrameExt_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ExtMsgID.h"
#include <ANY.h>
#include <asn_ioc.h>
#include "TestMsg.h"
#include "RTCMcorrections.h"
#include "PAMData.h"
#include "CLPMM.h"
#include "PersonalSafetyMessage.h"
#include "RoadsideCoordination.h"
#include "SensorSharingMsg.h"
#include "VehIntentionAndRequest.h"
#include "VehiclePaymentMessage.h"
#include <OPEN_TYPE.h>
#include <constr_CHOICE.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MessageFrameExt__value_PR {
	MessageFrameExt__value_PR_NOTHING,	/* No components present */
	MessageFrameExt__value_PR_TestMsg,
	MessageFrameExt__value_PR_RTCMcorrections,
	MessageFrameExt__value_PR_PAMData,
	MessageFrameExt__value_PR_CLPMM,
	MessageFrameExt__value_PR_PersonalSafetyMessage,
	MessageFrameExt__value_PR_RoadsideCoordination,
	MessageFrameExt__value_PR_SensorSharingMsg,
	MessageFrameExt__value_PR_VehIntentionAndRequest,
	MessageFrameExt__value_PR_VehiclePaymentMessage
} MessageFrameExt__value_PR;

/* MessageFrameExt */
typedef struct MessageFrameExt {
	ExtMsgID_t	 messageId;
	struct MessageFrameExt__value {
		MessageFrameExt__value_PR present;
		union MessageFrameExt__value_u {
			TestMsg_t	 TestMsg;
			RTCMcorrections_t	 RTCMcorrections;
			PAMData_t	 PAMData;
			CLPMM_t	 CLPMM;
			PersonalSafetyMessage_t	 PersonalSafetyMessage;
			RoadsideCoordination_t	 RoadsideCoordination;
			SensorSharingMsg_t	 SensorSharingMsg;
			VehIntentionAndRequest_t	 VehIntentionAndRequest;
			VehiclePaymentMessage_t	 VehiclePaymentMessage;
		} choice;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} value;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MessageFrameExt_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MessageFrameExt;
extern asn_SEQUENCE_specifics_t asn_SPC_MessageFrameExt_specs_1;
extern asn_TYPE_member_t asn_MBR_MessageFrameExt_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _MessageFrameExt_H_ */
#include <asn_internal.h>
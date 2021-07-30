/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciMsgLayerFrame_Response_H_
#define	_TciMsgLayerFrame_Response_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TciMsgLayerFrame_MsgID.h"
#include "TciMsgLayerFrame_ResultCode.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Exception;

/* Response */
typedef struct TciMsgLayerFrame_Response {
	TciMsgLayerFrame_MsgID_t	 msgId;
	TciMsgLayerFrame_ResultCode_t	 resultCode;
	struct Exception	*exception	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TciMsgLayerFrame_Response_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TciMsgLayerFrame_Response;
extern asn_SEQUENCE_specifics_t asn_SPC_TciMsgLayerFrame_Response_specs_1;
extern asn_TYPE_member_t asn_MBR_TciMsgLayerFrame_Response_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "TciMsgLayerFrame_Exception.h"

#endif	/* _TciMsgLayerFrame_Response_H_ */
#include <asn_internal.h>

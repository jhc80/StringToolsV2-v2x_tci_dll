/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciMsgLayerFrame_Exception_H_
#define	_TciMsgLayerFrame_Exception_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TciMsgLayerFrame_ExceptionType.h"
#include "TciMsgLayerFrame_ExceptionId.h"
#include "TciMsgLayerFrame_Module.h"
#include "TciMsgLayerFrame_ExceptionText.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Exception */
typedef struct TciMsgLayerFrame_Exception {
	TciMsgLayerFrame_ExceptionType_t	 eType;
	TciMsgLayerFrame_ExceptionId_t	 eId;
	TciMsgLayerFrame_Module_t	*eModule	/* OPTIONAL */;
	TciMsgLayerFrame_ExceptionText_t	*eDescription	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TciMsgLayerFrame_Exception_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TciMsgLayerFrame_Exception;
extern asn_SEQUENCE_specifics_t asn_SPC_TciMsgLayerFrame_Exception_specs_1;
extern asn_TYPE_member_t asn_MBR_TciMsgLayerFrame_Exception_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _TciMsgLayerFrame_Exception_H_ */
#include <asn_internal.h>

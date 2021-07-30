/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciSecMsgFrame_Exception_H_
#define	_TciSecMsgFrame_Exception_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TciSecMsgFrame_ExceptionType.h"
#include "TciSecMsgFrame_ExceptionId.h"
#include "TciSecMsgFrame_Module.h"
#include "TciSecMsgFrame_ExceptionText.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Exception */
typedef struct TciSecMsgFrame_Exception {
	TciSecMsgFrame_ExceptionType_t	 eType;
	TciSecMsgFrame_ExceptionId_t	*eId	/* OPTIONAL */;
	TciSecMsgFrame_Module_t	*eModule	/* OPTIONAL */;
	TciSecMsgFrame_ExceptionText_t	*eDescription	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TciSecMsgFrame_Exception_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_Exception;
extern asn_SEQUENCE_specifics_t asn_SPC_TciSecMsgFrame_Exception_specs_1;
extern asn_TYPE_member_t asn_MBR_TciSecMsgFrame_Exception_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _TciSecMsgFrame_Exception_H_ */
#include <asn_internal.h>

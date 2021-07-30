/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciNetworkLayer_H_
#define	_TciNetworkLayer_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <NumericString.h>
#include "TciNetworkLayerFrame_TciMsgFrame.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TciNetworkLayer */
typedef struct TciNetworkLayer {
	long	 version;
	NumericString_t	 msgNo;
	TciNetworkLayerFrame_TciMsgFrame_t	 msgFrame;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TciNetworkLayer_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TciNetworkLayer;

#ifdef __cplusplus
}
#endif

#endif	/* _TciNetworkLayer_H_ */
#include <asn_internal.h>

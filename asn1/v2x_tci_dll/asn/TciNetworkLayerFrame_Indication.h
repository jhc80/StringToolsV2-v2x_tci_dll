/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciNetworkLayerFrame_Indication_H_
#define	_TciNetworkLayerFrame_Indication_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TciNetworkLayerFrame_Event.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct NetworkLayerFrame;
struct Exception;

/* Indication */
typedef struct TciNetworkLayerFrame_Indication {
	TciNetworkLayerFrame_Event_t	 event;
	struct NetworkLayerFrame	*networkLayerFrame	/* OPTIONAL */;
	struct Exception	*exceptionInfo	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TciNetworkLayerFrame_Indication_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TciNetworkLayerFrame_Indication;
extern asn_SEQUENCE_specifics_t asn_SPC_TciNetworkLayerFrame_Indication_specs_1;
extern asn_TYPE_member_t asn_MBR_TciNetworkLayerFrame_Indication_1[3];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "NetworkLayerFrame.h"
#include "TciNetworkLayerFrame_Exception.h"

#endif	/* _TciNetworkLayerFrame_Indication_H_ */
#include <asn_internal.h>

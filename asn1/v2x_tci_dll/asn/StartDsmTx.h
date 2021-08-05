/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_StartDsmTx_H_
#define	_StartDsmTx_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TciNetworkLayerFrame_Aid.h"
#include "TciNetworkLayerFrame_RepeatRate.h"
#include "DsmData.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* StartDsmTx */
typedef struct StartDsmTx {
	TciNetworkLayerFrame_Aid_t	 aid;
	TciNetworkLayerFrame_RepeatRate_t	 repeatRate;
	DsmData_t	*payload	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} StartDsmTx_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_StartDsmTx;
extern asn_SEQUENCE_specifics_t asn_SPC_StartDsmTx_specs_1;
extern asn_TYPE_member_t asn_MBR_StartDsmTx_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _StartDsmTx_H_ */
#include <asn_internal.h>
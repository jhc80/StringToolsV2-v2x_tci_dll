/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SetMibInfo_H_
#define	_SetMibInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DsmMaxLength.h"
#include <constr_CHOICE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SetMibInfo_PR {
	SetMibInfo_PR_NOTHING,	/* No components present */
	SetMibInfo_PR_dsmMaxLength
	/* Extensions may appear below */
	
} SetMibInfo_PR;

/* SetMibInfo */
typedef struct SetMibInfo {
	SetMibInfo_PR present;
	union SetMibInfo_u {
		DsmMaxLength_t	 dsmMaxLength;
		/*
		 * This type is extensible,
		 * possible extensions are below.
		 */
	} choice;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetMibInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetMibInfo;
extern asn_CHOICE_specifics_t asn_SPC_SetMibInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_SetMibInfo_1[1];
extern asn_per_constraints_t asn_PER_type_SetMibInfo_constr_1;

#ifdef __cplusplus
}
#endif

#endif	/* _SetMibInfo_H_ */
#include <asn_internal.h>

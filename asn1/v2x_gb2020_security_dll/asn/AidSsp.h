/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityBaseDataTypes"
 * 	found in "asn/SecurityBaseDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_AidSsp_H_
#define	_AidSsp_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Aid.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct ServiceSpecificPermissions;

/* AidSsp */
typedef struct AidSsp {
	Aid_t	 aid;
	struct ServiceSpecificPermissions	*ssp	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} AidSsp_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_AidSsp;
extern asn_SEQUENCE_specifics_t asn_SPC_AidSsp_specs_1;
extern asn_TYPE_member_t asn_MBR_AidSsp_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "ServiceSpecificPermissions.h"

#endif	/* _AidSsp_H_ */
#include <asn_internal.h>
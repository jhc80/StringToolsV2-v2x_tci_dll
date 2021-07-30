/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ScmsSsp"
 * 	found in "asn/ScmsSsp.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_RootCaSsp_H_
#define	_RootCaSsp_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint8.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* RootCaSsp */
typedef struct RootCaSsp {
	Uint8_t	 version;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} RootCaSsp_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_RootCaSsp;
extern asn_SEQUENCE_specifics_t asn_SPC_RootCaSsp_specs_1;
extern asn_TYPE_member_t asn_MBR_RootCaSsp_1[1];

#ifdef __cplusplus
}
#endif

#endif	/* _RootCaSsp_H_ */
#include <asn_internal.h>

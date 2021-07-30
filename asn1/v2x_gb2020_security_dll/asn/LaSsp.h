/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ScmsSsp"
 * 	found in "asn/ScmsSsp.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_LaSsp_H_
#define	_LaSsp_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint8.h"
#include "Uint16.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LaSsp */
typedef struct LaSsp {
	Uint8_t	 version;
	Uint16_t	 laId;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LaSsp_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LaSsp;
extern asn_SEQUENCE_specifics_t asn_SPC_LaSsp_specs_1;
extern asn_TYPE_member_t asn_MBR_LaSsp_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _LaSsp_H_ */
#include <asn_internal.h>

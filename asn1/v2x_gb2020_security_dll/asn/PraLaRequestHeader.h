/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaRaInterfacePdu"
 * 	found in "asn/LaRaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PraLaRequestHeader_H_
#define	_PraLaRequestHeader_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint16.h"
#include "Hostname.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PraLaRequestHeader */
typedef struct PraLaRequestHeader {
	Uint16_t	 iMin;
	Uint16_t	 iMax;
	Hostname_t	 praId;
	Hostname_t	 pcaId;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PraLaRequestHeader_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PraLaRequestHeader;
extern asn_SEQUENCE_specifics_t asn_SPC_PraLaRequestHeader_specs_1;
extern asn_TYPE_member_t asn_MBR_PraLaRequestHeader_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _PraLaRequestHeader_H_ */
#include <asn_internal.h>

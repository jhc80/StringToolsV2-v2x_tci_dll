/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_VehSize_H_
#define	_VehSize_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* VehSize */
typedef struct VehSize {
	long	 width;
	long	 length;
	long	*height	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} VehSize_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_VehSize;
extern asn_SEQUENCE_specifics_t asn_SPC_VehSize_specs_1;
extern asn_TYPE_member_t asn_MBR_VehSize_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _VehSize_H_ */
#include <asn_internal.h>

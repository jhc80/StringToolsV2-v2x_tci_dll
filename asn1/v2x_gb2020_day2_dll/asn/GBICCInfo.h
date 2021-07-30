/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_GBICCInfo_H_
#define	_GBICCInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GBICCInfo */
typedef struct GBICCInfo {
	OCTET_STRING_t	 iccIssueInfo;
	OCTET_STRING_t	 iccUniTollInfo;
	OCTET_STRING_t	 iccBalance;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} GBICCInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GBICCInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_GBICCInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_GBICCInfo_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _GBICCInfo_H_ */
#include <asn_internal.h>

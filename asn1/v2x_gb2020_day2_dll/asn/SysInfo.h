/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SysInfo_H_
#define	_SysInfo_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>
#include <NativeInteger.h>
#include "Date.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* SysInfo */
typedef struct SysInfo {
	OCTET_STRING_t	 contractProvider;
	long	 contractType;
	long	 contractVersion;
	OCTET_STRING_t	 contractSerialNumer;
	Date_t	 contractSignedDate;
	Date_t	 contractExpiredDate;
	OCTET_STRING_t	 reserved;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SysInfo_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SysInfo;
extern asn_SEQUENCE_specifics_t asn_SPC_SysInfo_specs_1;
extern asn_TYPE_member_t asn_MBR_SysInfo_1[7];

#ifdef __cplusplus
}
#endif

#endif	/* _SysInfo_H_ */
#include <asn_internal.h>

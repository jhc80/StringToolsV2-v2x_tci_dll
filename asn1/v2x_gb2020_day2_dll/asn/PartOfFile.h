/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_PartOfFile_H_
#define	_PartOfFile_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include "File.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PartOfFile */
typedef struct PartOfFile {
	long	 offset;
	long	 length;
	File_t	 fileContent;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PartOfFile_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PartOfFile;
extern asn_SEQUENCE_specifics_t asn_SPC_PartOfFile_specs_1;
extern asn_TYPE_member_t asn_MBR_PartOfFile_1[3];

#ifdef __cplusplus
}
#endif

#endif	/* _PartOfFile_H_ */
#include <asn_internal.h>

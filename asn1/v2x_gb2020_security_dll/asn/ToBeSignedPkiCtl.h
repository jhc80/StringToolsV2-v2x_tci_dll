/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CTL"
 * 	found in "asn/CTL.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ToBeSignedPkiCtl_H_
#define	_ToBeSignedPkiCtl_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Uint8.h"
#include "IssuerIdentifier.h"
#include "Uint16.h"
#include "Time32.h"
#include "SequenceOfPkiCertInfo.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ToBeSignedPkiCtl */
typedef struct ToBeSignedPkiCtl {
	Uint8_t	 version;
	IssuerIdentifier_t	 issuer;
	Uint16_t	 series;
	Time32_t	 issueDate;
	Time32_t	 nextPkiCtl;
	SequenceOfPkiCertInfo_t	 pkiCertInfoList;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} ToBeSignedPkiCtl_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ToBeSignedPkiCtl;
extern asn_SEQUENCE_specifics_t asn_SPC_ToBeSignedPkiCtl_specs_1;
extern asn_TYPE_member_t asn_MBR_ToBeSignedPkiCtl_1[6];

#ifdef __cplusplus
}
#endif

#endif	/* _ToBeSignedPkiCtl_H_ */
#include <asn_internal.h>

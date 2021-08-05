/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SecurityResultCode_H_
#define	_SecurityResultCode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SecurityResultCode {
	SecurityResultCode_unknown	= 0,
	SecurityResultCode_incorrectSecureMessageVersion	= 1,
	SecurityResultCode_incorrectSignerType	= 2,
	SecurityResultCode_incorrectCertVersion	= 3,
	SecurityResultCode_incorrectCertIssueDigest	= 4,
	SecurityResultCode_incorrectCertSubjectInfo	= 5,
	SecurityResultCode_incorrectCertSubjectAttribute	= 6,
	SecurityResultCode_incorrectCertValidityPeriod	= 7,
	SecurityResultCode_incorrectCertTimeStartAndEnd	= 8,
	SecurityResultCode_incorrectSubcertAuthority	= 9,
	SecurityResultCode_incorrectCertChain	= 10,
	SecurityResultCode_incorrectCertSignature	= 11,
	SecurityResultCode_incorrectTbsDataGenTime	= 12,
	SecurityResultCode_incorrectTbsDataHashAlg	= 13,
	SecurityResultCode_incorrectTbsDataItsAid	= 14,
	SecurityResultCode_incorrectSignedMessageSignature	= 15
	/*
	 * Enumeration is extensible
	 */
} e_SecurityResultCode;

/* SecurityResultCode */
typedef long	 SecurityResultCode_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_SecurityResultCode_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_SecurityResultCode;
extern const asn_INTEGER_specifics_t asn_SPC_SecurityResultCode_specs_1;
asn_struct_free_f SecurityResultCode_free;
asn_struct_print_f SecurityResultCode_print;
asn_constr_check_f SecurityResultCode_constraint;
ber_type_decoder_f SecurityResultCode_decode_ber;
der_type_encoder_f SecurityResultCode_encode_der;
xer_type_decoder_f SecurityResultCode_decode_xer;
xer_type_encoder_f SecurityResultCode_encode_xer;
oer_type_decoder_f SecurityResultCode_decode_oer;
oer_type_encoder_f SecurityResultCode_encode_oer;
per_type_decoder_f SecurityResultCode_decode_uper;
per_type_encoder_f SecurityResultCode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SecurityResultCode_H_ */
#include <asn_internal.h>
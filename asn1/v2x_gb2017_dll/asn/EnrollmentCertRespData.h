/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_EnrollmentCertRespData_H_
#define	_EnrollmentCertRespData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SecureMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

/* EnrollmentCertRespData */
typedef SecureMessage_t	 EnrollmentCertRespData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EnrollmentCertRespData;
asn_struct_free_f EnrollmentCertRespData_free;
asn_struct_print_f EnrollmentCertRespData_print;
asn_constr_check_f EnrollmentCertRespData_constraint;
ber_type_decoder_f EnrollmentCertRespData_decode_ber;
der_type_encoder_f EnrollmentCertRespData_encode_der;
xer_type_decoder_f EnrollmentCertRespData_decode_xer;
xer_type_encoder_f EnrollmentCertRespData_encode_xer;
oer_type_decoder_f EnrollmentCertRespData_decode_oer;
oer_type_encoder_f EnrollmentCertRespData_encode_oer;
per_type_decoder_f EnrollmentCertRespData_decode_uper;
per_type_encoder_f EnrollmentCertRespData_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _EnrollmentCertRespData_H_ */
#include <asn_internal.h>

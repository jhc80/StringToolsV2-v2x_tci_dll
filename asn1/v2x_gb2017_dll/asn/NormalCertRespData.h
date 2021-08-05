/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_NormalCertRespData_H_
#define	_NormalCertRespData_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SecureMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

/* NormalCertRespData */
typedef SecureMessage_t	 NormalCertRespData_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NormalCertRespData;
asn_struct_free_f NormalCertRespData_free;
asn_struct_print_f NormalCertRespData_print;
asn_constr_check_f NormalCertRespData_constraint;
ber_type_decoder_f NormalCertRespData_decode_ber;
der_type_encoder_f NormalCertRespData_encode_der;
xer_type_decoder_f NormalCertRespData_decode_xer;
xer_type_encoder_f NormalCertRespData_encode_xer;
oer_type_decoder_f NormalCertRespData_decode_oer;
oer_type_encoder_f NormalCertRespData_encode_oer;
per_type_decoder_f NormalCertRespData_decode_uper;
per_type_encoder_f NormalCertRespData_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _NormalCertRespData_H_ */
#include <asn_internal.h>
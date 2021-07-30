/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TextUTF8_H_
#define	_TextUTF8_H_


#include <asn_application.h>

/* Including external dependencies */
#include <OCTET_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TextUTF8 */
typedef OCTET_STRING_t	 TextUTF8_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TextUTF8_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TextUTF8;
asn_struct_free_f TextUTF8_free;
asn_struct_print_f TextUTF8_print;
asn_constr_check_f TextUTF8_constraint;
ber_type_decoder_f TextUTF8_decode_ber;
der_type_encoder_f TextUTF8_encode_der;
xer_type_decoder_f TextUTF8_decode_xer;
xer_type_encoder_f TextUTF8_encode_xer;
oer_type_decoder_f TextUTF8_decode_oer;
oer_type_encoder_f TextUTF8_encode_oer;
per_type_decoder_f TextUTF8_decode_uper;
per_type_encoder_f TextUTF8_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TextUTF8_H_ */
#include <asn_internal.h>

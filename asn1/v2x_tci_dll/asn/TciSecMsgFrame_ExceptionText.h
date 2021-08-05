/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciSecMsgFrame_ExceptionText_H_
#define	_TciSecMsgFrame_ExceptionText_H_


#include <asn_application.h>

/* Including external dependencies */
#include <UTF8String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ExceptionText */
typedef UTF8String_t	 TciSecMsgFrame_ExceptionText_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciSecMsgFrame_ExceptionText_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_ExceptionText;
asn_struct_free_f TciSecMsgFrame_ExceptionText_free;
asn_struct_print_f TciSecMsgFrame_ExceptionText_print;
asn_constr_check_f TciSecMsgFrame_ExceptionText_constraint;
ber_type_decoder_f TciSecMsgFrame_ExceptionText_decode_ber;
der_type_encoder_f TciSecMsgFrame_ExceptionText_encode_der;
xer_type_decoder_f TciSecMsgFrame_ExceptionText_decode_xer;
xer_type_encoder_f TciSecMsgFrame_ExceptionText_encode_xer;
oer_type_decoder_f TciSecMsgFrame_ExceptionText_decode_oer;
oer_type_encoder_f TciSecMsgFrame_ExceptionText_encode_oer;
per_type_decoder_f TciSecMsgFrame_ExceptionText_decode_uper;
per_type_encoder_f TciSecMsgFrame_ExceptionText_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciSecMsgFrame_ExceptionText_H_ */
#include <asn_internal.h>
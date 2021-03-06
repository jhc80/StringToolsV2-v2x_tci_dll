/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SignedMessage_H_
#define	_SignedMessage_H_


#include <asn_application.h>

/* Including external dependencies */
#include "SecureMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

/* SignedMessage */
typedef SecureMessage_t	 SignedMessage_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_SignedMessage_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_SignedMessage;
asn_struct_free_f SignedMessage_free;
asn_struct_print_f SignedMessage_print;
asn_constr_check_f SignedMessage_constraint;
ber_type_decoder_f SignedMessage_decode_ber;
der_type_encoder_f SignedMessage_encode_der;
xer_type_decoder_f SignedMessage_decode_xer;
xer_type_encoder_f SignedMessage_encode_xer;
oer_type_decoder_f SignedMessage_decode_oer;
oer_type_encoder_f SignedMessage_encode_oer;
per_type_decoder_f SignedMessage_decode_uper;
per_type_encoder_f SignedMessage_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SignedMessage_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DefTime"
 * 	found in "asn/DefTime.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_DHour_H_
#define	_DHour_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* DHour */
typedef long	 DHour_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_DHour_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_DHour;
asn_struct_free_f DHour_free;
asn_struct_print_f DHour_print;
asn_constr_check_f DHour_constraint;
ber_type_decoder_f DHour_decode_ber;
der_type_encoder_f DHour_encode_der;
xer_type_decoder_f DHour_decode_xer;
xer_type_encoder_f DHour_encode_xer;
oer_type_decoder_f DHour_decode_oer;
oer_type_encoder_f DHour_encode_oer;
per_type_decoder_f DHour_decode_uper;
per_type_encoder_f DHour_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _DHour_H_ */
#include <asn_internal.h>

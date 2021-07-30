/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ChannelID_H_
#define	_ChannelID_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ChannelID {
	ChannelID_obu	= 0,
	ChannelID_esam	= 1,
	ChannelID_icc	= 2,
	ChannelID_hmi	= 3,
	ChannelID_beeper	= 4
} e_ChannelID;

/* ChannelID */
typedef long	 ChannelID_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ChannelID_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ChannelID;
extern const asn_INTEGER_specifics_t asn_SPC_ChannelID_specs_1;
asn_struct_free_f ChannelID_free;
asn_struct_print_f ChannelID_print;
asn_constr_check_f ChannelID_constraint;
ber_type_decoder_f ChannelID_decode_ber;
der_type_encoder_f ChannelID_encode_der;
xer_type_decoder_f ChannelID_decode_xer;
xer_type_encoder_f ChannelID_encode_xer;
oer_type_decoder_f ChannelID_decode_oer;
oer_type_encoder_f ChannelID_encode_oer;
per_type_decoder_f ChannelID_decode_uper;
per_type_encoder_f ChannelID_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ChannelID_H_ */
#include <asn_internal.h>

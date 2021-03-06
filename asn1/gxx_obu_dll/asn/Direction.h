/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Direction_H_
#define	_Direction_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Direction {
	Direction_others	= 0,
	Direction_ahead	= 1,
	Direction_aheadLeft	= 2,
	Direction_aheadRight	= 3,
	Direction_behind	= 4,
	Direction_behindLeft	= 5,
	Direction_behindRight	= 6,
	Direction_onComing	= 7,
	Direction_onComingLeft	= 8,
	Direction_onComingRight	= 9,
	Direction_intsLeft	= 10,
	Direction_intsRight	= 11
} e_Direction;

/* Direction */
typedef long	 Direction_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_Direction_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_Direction;
extern const asn_INTEGER_specifics_t asn_SPC_Direction_specs_1;
asn_struct_free_f Direction_free;
asn_struct_print_f Direction_print;
asn_constr_check_f Direction_constraint;
ber_type_decoder_f Direction_decode_ber;
der_type_encoder_f Direction_encode_der;
xer_type_decoder_f Direction_decode_xer;
xer_type_encoder_f Direction_encode_xer;
oer_type_decoder_f Direction_decode_oer;
oer_type_encoder_f Direction_encode_oer;
per_type_decoder_f Direction_decode_uper;
per_type_encoder_f Direction_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Direction_H_ */
#include <asn_internal.h>

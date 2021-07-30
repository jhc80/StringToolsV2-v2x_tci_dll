/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SPATIntersectionState"
 * 	found in "asn/SPATIntersectionState.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_LightState_H_
#define	_LightState_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum LightState {
	LightState_unavailable	= 0,
	LightState_dark	= 1,
	LightState_flashing_red	= 2,
	LightState_red	= 3,
	LightState_flashing_green	= 4,
	LightState_permissive_green	= 5,
	LightState_protected_green	= 6,
	LightState_yellow	= 7,
	LightState_flashing_yellow	= 8
	/*
	 * Enumeration is extensible
	 */
} e_LightState;

/* LightState */
typedef long	 LightState_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_LightState_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_LightState;
extern const asn_INTEGER_specifics_t asn_SPC_LightState_specs_1;
asn_struct_free_f LightState_free;
asn_struct_print_f LightState_print;
asn_constr_check_f LightState_constraint;
ber_type_decoder_f LightState_decode_ber;
der_type_encoder_f LightState_encode_der;
xer_type_decoder_f LightState_decode_xer;
xer_type_encoder_f LightState_encode_xer;
oer_type_decoder_f LightState_decode_oer;
oer_type_encoder_f LightState_encode_oer;
per_type_decoder_f LightState_decode_uper;
per_type_encoder_f LightState_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _LightState_H_ */
#include <asn_internal.h>

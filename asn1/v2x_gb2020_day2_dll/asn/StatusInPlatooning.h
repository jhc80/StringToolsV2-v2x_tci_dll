/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Platooning"
 * 	found in "asn/Platooning.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_StatusInPlatooning_H_
#define	_StatusInPlatooning_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum StatusInPlatooning {
	StatusInPlatooning_navigating	= 0,
	StatusInPlatooning_beginToDissmiss	= 1,
	StatusInPlatooning_askForJoining	= 2,
	StatusInPlatooning_joining	= 3,
	StatusInPlatooning_following	= 4,
	StatusInPlatooning_askForLeaving	= 5,
	StatusInPlatooning_leaving	= 6
	/*
	 * Enumeration is extensible
	 */
} e_StatusInPlatooning;

/* StatusInPlatooning */
typedef long	 StatusInPlatooning_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_StatusInPlatooning_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_StatusInPlatooning;
extern const asn_INTEGER_specifics_t asn_SPC_StatusInPlatooning_specs_1;
asn_struct_free_f StatusInPlatooning_free;
asn_struct_print_f StatusInPlatooning_print;
asn_constr_check_f StatusInPlatooning_constraint;
ber_type_decoder_f StatusInPlatooning_decode_ber;
der_type_encoder_f StatusInPlatooning_encode_der;
xer_type_decoder_f StatusInPlatooning_decode_xer;
xer_type_encoder_f StatusInPlatooning_encode_xer;
oer_type_decoder_f StatusInPlatooning_decode_oer;
oer_type_encoder_f StatusInPlatooning_encode_oer;
per_type_decoder_f StatusInPlatooning_decode_uper;
per_type_encoder_f StatusInPlatooning_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _StatusInPlatooning_H_ */
#include <asn_internal.h>

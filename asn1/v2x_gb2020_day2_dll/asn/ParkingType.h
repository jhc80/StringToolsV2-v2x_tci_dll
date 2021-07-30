/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "asn/PAM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ParkingType_H_
#define	_ParkingType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ParkingType {
	ParkingType_unknown	= 0,
	ParkingType_ordinary	= 1,
	ParkingType_disabled	= 2,
	ParkingType_mini	= 3,
	ParkingType_attached	= 4,
	ParkingType_charging	= 5,
	ParkingType_stereo	= 6,
	ParkingType_lady	= 7,
	ParkingType_extended	= 8,
	ParkingType_private	= 9
} e_ParkingType;

/* ParkingType */
typedef BIT_STRING_t	 ParkingType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ParkingType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ParkingType;
asn_struct_free_f ParkingType_free;
asn_struct_print_f ParkingType_print;
asn_constr_check_f ParkingType_constraint;
ber_type_decoder_f ParkingType_decode_ber;
der_type_encoder_f ParkingType_encode_der;
xer_type_decoder_f ParkingType_decode_xer;
xer_type_encoder_f ParkingType_encode_xer;
oer_type_decoder_f ParkingType_decode_oer;
oer_type_encoder_f ParkingType_encode_oer;
per_type_decoder_f ParkingType_decode_uper;
per_type_encoder_f ParkingType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ParkingType_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VehBrake"
 * 	found in "asn/VehBrake.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_BrakeAppliedStatus_H_
#define	_BrakeAppliedStatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum BrakeAppliedStatus {
	BrakeAppliedStatus_unavailable	= 0,
	BrakeAppliedStatus_leftFront	= 1,
	BrakeAppliedStatus_leftRear	= 2,
	BrakeAppliedStatus_rightFront	= 3,
	BrakeAppliedStatus_rightRear	= 4
} e_BrakeAppliedStatus;

/* BrakeAppliedStatus */
typedef BIT_STRING_t	 BrakeAppliedStatus_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_BrakeAppliedStatus_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_BrakeAppliedStatus;
asn_struct_free_f BrakeAppliedStatus_free;
asn_struct_print_f BrakeAppliedStatus_print;
asn_constr_check_f BrakeAppliedStatus_constraint;
ber_type_decoder_f BrakeAppliedStatus_decode_ber;
der_type_encoder_f BrakeAppliedStatus_encode_der;
xer_type_decoder_f BrakeAppliedStatus_decode_xer;
xer_type_encoder_f BrakeAppliedStatus_encode_xer;
oer_type_decoder_f BrakeAppliedStatus_decode_oer;
oer_type_encoder_f BrakeAppliedStatus_encode_oer;
per_type_decoder_f BrakeAppliedStatus_decode_uper;
per_type_encoder_f BrakeAppliedStatus_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _BrakeAppliedStatus_H_ */
#include <asn_internal.h>

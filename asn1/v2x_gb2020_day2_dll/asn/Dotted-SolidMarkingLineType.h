/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Map"
 * 	found in "asn/Map.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Dotted_SolidMarkingLineType_H_
#define	_Dotted_SolidMarkingLineType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum Dotted_SolidMarkingLineType {
	Dotted_SolidMarkingLineType_whiteDottedLine	= 0,
	Dotted_SolidMarkingLineType_whiteSolidLine	= 1,
	Dotted_SolidMarkingLineType_yellowDottedLine	= 2,
	Dotted_SolidMarkingLineType_yellowSolidLine	= 3,
	Dotted_SolidMarkingLineType_whiteDotted_solidLine	= 4,
	Dotted_SolidMarkingLineType_whiteSotted_dottedLine	= 5,
	Dotted_SolidMarkingLineType_yellowDotted_solidLine	= 6,
	Dotted_SolidMarkingLineType_yellowSotted_dottedLine	= 7
	/*
	 * Enumeration is extensible
	 */
} e_Dotted_SolidMarkingLineType;

/* Dotted-SolidMarkingLineType */
typedef long	 Dotted_SolidMarkingLineType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_Dotted_SolidMarkingLineType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_Dotted_SolidMarkingLineType;
extern const asn_INTEGER_specifics_t asn_SPC_Dotted_SolidMarkingLineType_specs_1;
asn_struct_free_f Dotted_SolidMarkingLineType_free;
asn_struct_print_f Dotted_SolidMarkingLineType_print;
asn_constr_check_f Dotted_SolidMarkingLineType_constraint;
ber_type_decoder_f Dotted_SolidMarkingLineType_decode_ber;
der_type_encoder_f Dotted_SolidMarkingLineType_encode_der;
xer_type_decoder_f Dotted_SolidMarkingLineType_decode_xer;
xer_type_encoder_f Dotted_SolidMarkingLineType_encode_xer;
oer_type_decoder_f Dotted_SolidMarkingLineType_decode_oer;
oer_type_encoder_f Dotted_SolidMarkingLineType_encode_oer;
per_type_decoder_f Dotted_SolidMarkingLineType_decode_uper;
per_type_encoder_f Dotted_SolidMarkingLineType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Dotted_SolidMarkingLineType_H_ */
#include <asn_internal.h>
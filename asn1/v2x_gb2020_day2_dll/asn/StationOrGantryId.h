/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_StationOrGantryId_H_
#define	_StationOrGantryId_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* StationOrGantryId */
typedef unsigned long	 StationOrGantryId_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_StationOrGantryId_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_StationOrGantryId;
extern const asn_INTEGER_specifics_t asn_SPC_StationOrGantryId_specs_1;
asn_struct_free_f StationOrGantryId_free;
asn_struct_print_f StationOrGantryId_print;
asn_constr_check_f StationOrGantryId_constraint;
ber_type_decoder_f StationOrGantryId_decode_ber;
der_type_encoder_f StationOrGantryId_encode_der;
xer_type_decoder_f StationOrGantryId_decode_xer;
xer_type_encoder_f StationOrGantryId_encode_xer;
oer_type_decoder_f StationOrGantryId_decode_oer;
oer_type_encoder_f StationOrGantryId_encode_oer;
per_type_decoder_f StationOrGantryId_decode_uper;
per_type_encoder_f StationOrGantryId_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _StationOrGantryId_H_ */
#include <asn_internal.h>

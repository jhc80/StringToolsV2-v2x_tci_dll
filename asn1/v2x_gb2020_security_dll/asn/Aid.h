/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SecurityBaseDataTypes"
 * 	found in "asn/SecurityBaseDataTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_Aid_H_
#define	_Aid_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Aid */
typedef unsigned long	 Aid_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_Aid_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_Aid;
extern const asn_INTEGER_specifics_t asn_SPC_Aid_specs_1;
asn_struct_free_f Aid_free;
asn_struct_print_f Aid_print;
asn_constr_check_f Aid_constraint;
ber_type_decoder_f Aid_decode_ber;
der_type_encoder_f Aid_encode_der;
xer_type_decoder_f Aid_decode_xer;
xer_type_encoder_f Aid_encode_xer;
oer_type_decoder_f Aid_decode_oer;
oer_type_encoder_f Aid_encode_oer;
per_type_decoder_f Aid_decode_uper;
per_type_encoder_f Aid_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _Aid_H_ */
#include <asn_internal.h>
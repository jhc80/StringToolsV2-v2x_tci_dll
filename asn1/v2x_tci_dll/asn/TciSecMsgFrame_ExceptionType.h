/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciSecMsgFrame_ExceptionType_H_
#define	_TciSecMsgFrame_ExceptionType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TciSecMsgFrame_ExceptionType {
	TciSecMsgFrame_ExceptionType_info	= 0,
	TciSecMsgFrame_ExceptionType_warning	= 1,
	TciSecMsgFrame_ExceptionType_error	= 2
} e_TciSecMsgFrame_ExceptionType;

/* ExceptionType */
typedef long	 TciSecMsgFrame_ExceptionType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciSecMsgFrame_ExceptionType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_ExceptionType;
extern const asn_INTEGER_specifics_t asn_SPC_TciSecMsgFrame_ExceptionType_specs_1;
asn_struct_free_f TciSecMsgFrame_ExceptionType_free;
asn_struct_print_f TciSecMsgFrame_ExceptionType_print;
asn_constr_check_f TciSecMsgFrame_ExceptionType_constraint;
ber_type_decoder_f TciSecMsgFrame_ExceptionType_decode_ber;
der_type_encoder_f TciSecMsgFrame_ExceptionType_encode_der;
xer_type_decoder_f TciSecMsgFrame_ExceptionType_decode_xer;
xer_type_encoder_f TciSecMsgFrame_ExceptionType_encode_xer;
oer_type_decoder_f TciSecMsgFrame_ExceptionType_decode_oer;
oer_type_encoder_f TciSecMsgFrame_ExceptionType_encode_oer;
per_type_decoder_f TciSecMsgFrame_ExceptionType_decode_uper;
per_type_encoder_f TciSecMsgFrame_ExceptionType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciSecMsgFrame_ExceptionType_H_ */
#include <asn_internal.h>
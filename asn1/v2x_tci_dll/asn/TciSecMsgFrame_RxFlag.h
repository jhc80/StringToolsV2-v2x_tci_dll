/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciSecMsgFrame_RxFlag_H_
#define	_TciSecMsgFrame_RxFlag_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TciSecMsgFrame_RxFlag {
	TciSecMsgFrame_RxFlag_recvAidMatch	= 0
	/*
	 * Enumeration is extensible
	 */
} e_TciSecMsgFrame_RxFlag;

/* RxFlag */
typedef long	 TciSecMsgFrame_RxFlag_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciSecMsgFrame_RxFlag_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_RxFlag;
extern const asn_INTEGER_specifics_t asn_SPC_TciSecMsgFrame_RxFlag_specs_1;
asn_struct_free_f TciSecMsgFrame_RxFlag_free;
asn_struct_print_f TciSecMsgFrame_RxFlag_print;
asn_constr_check_f TciSecMsgFrame_RxFlag_constraint;
ber_type_decoder_f TciSecMsgFrame_RxFlag_decode_ber;
der_type_encoder_f TciSecMsgFrame_RxFlag_encode_der;
xer_type_decoder_f TciSecMsgFrame_RxFlag_decode_xer;
xer_type_encoder_f TciSecMsgFrame_RxFlag_encode_xer;
oer_type_decoder_f TciSecMsgFrame_RxFlag_decode_oer;
oer_type_encoder_f TciSecMsgFrame_RxFlag_encode_oer;
per_type_decoder_f TciSecMsgFrame_RxFlag_decode_uper;
per_type_encoder_f TciSecMsgFrame_RxFlag_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciSecMsgFrame_RxFlag_H_ */
#include <asn_internal.h>

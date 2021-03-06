/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ParamInRsm_H_
#define	_ParamInRsm_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ParamInRsm {
	ParamInRsm_containsBasicRSM	= 0,
	ParamInRsm_containsPtcData	= 1
} e_ParamInRsm;

/* ParamInRsm */
typedef BIT_STRING_t	 ParamInRsm_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ParamInRsm;
asn_struct_free_f ParamInRsm_free;
asn_struct_print_f ParamInRsm_print;
asn_constr_check_f ParamInRsm_constraint;
ber_type_decoder_f ParamInRsm_decode_ber;
der_type_encoder_f ParamInRsm_encode_der;
xer_type_decoder_f ParamInRsm_decode_xer;
xer_type_encoder_f ParamInRsm_encode_xer;
oer_type_decoder_f ParamInRsm_decode_oer;
oer_type_encoder_f ParamInRsm_encode_oer;
per_type_decoder_f ParamInRsm_decode_uper;
per_type_encoder_f ParamInRsm_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ParamInRsm_H_ */
#include <asn_internal.h>

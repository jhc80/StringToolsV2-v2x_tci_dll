/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciNetworkLayerFrame_ResultCode_H_
#define	_TciNetworkLayerFrame_ResultCode_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TciNetworkLayerFrame_ResultCode {
	TciNetworkLayerFrame_ResultCode_rcSuccess	= 0,
	TciNetworkLayerFrame_ResultCode_rcFailure	= 1
} e_TciNetworkLayerFrame_ResultCode;

/* ResultCode */
typedef long	 TciNetworkLayerFrame_ResultCode_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciNetworkLayerFrame_ResultCode_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciNetworkLayerFrame_ResultCode;
extern const asn_INTEGER_specifics_t asn_SPC_TciNetworkLayerFrame_ResultCode_specs_1;
asn_struct_free_f TciNetworkLayerFrame_ResultCode_free;
asn_struct_print_f TciNetworkLayerFrame_ResultCode_print;
asn_constr_check_f TciNetworkLayerFrame_ResultCode_constraint;
ber_type_decoder_f TciNetworkLayerFrame_ResultCode_decode_ber;
der_type_encoder_f TciNetworkLayerFrame_ResultCode_encode_der;
xer_type_decoder_f TciNetworkLayerFrame_ResultCode_decode_xer;
xer_type_encoder_f TciNetworkLayerFrame_ResultCode_encode_xer;
oer_type_decoder_f TciNetworkLayerFrame_ResultCode_decode_oer;
oer_type_encoder_f TciNetworkLayerFrame_ResultCode_encode_oer;
per_type_decoder_f TciNetworkLayerFrame_ResultCode_decode_uper;
per_type_encoder_f TciNetworkLayerFrame_ResultCode_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciNetworkLayerFrame_ResultCode_H_ */
#include <asn_internal.h>

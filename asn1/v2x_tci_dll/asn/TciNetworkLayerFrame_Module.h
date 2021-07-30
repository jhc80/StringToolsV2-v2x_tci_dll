/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciNetworkLayerFrame_Module_H_
#define	_TciNetworkLayerFrame_Module_H_


#include <asn_application.h>

/* Including external dependencies */
#include <UTF8String.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Module */
typedef UTF8String_t	 TciNetworkLayerFrame_Module_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciNetworkLayerFrame_Module_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciNetworkLayerFrame_Module;
asn_struct_free_f TciNetworkLayerFrame_Module_free;
asn_struct_print_f TciNetworkLayerFrame_Module_print;
asn_constr_check_f TciNetworkLayerFrame_Module_constraint;
ber_type_decoder_f TciNetworkLayerFrame_Module_decode_ber;
der_type_encoder_f TciNetworkLayerFrame_Module_encode_der;
xer_type_decoder_f TciNetworkLayerFrame_Module_decode_xer;
xer_type_encoder_f TciNetworkLayerFrame_Module_encode_xer;
oer_type_decoder_f TciNetworkLayerFrame_Module_decode_oer;
oer_type_encoder_f TciNetworkLayerFrame_Module_encode_oer;
per_type_decoder_f TciNetworkLayerFrame_Module_decode_uper;
per_type_encoder_f TciNetworkLayerFrame_Module_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciNetworkLayerFrame_Module_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_ParamInMap_H_
#define	_ParamInMap_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ParamInMap {
	ParamInMap_containsBasicMapNodesInfo	= 0,
	ParamInMap_containsBasicMapLinkInfo	= 1,
	ParamInMap_containsBasicMapLaneInfo	= 2,
	ParamInMap_containsConnectsToList	= 3,
	ParamInMap_containsAllowedManeuvers	= 4
} e_ParamInMap;

/* ParamInMap */
typedef BIT_STRING_t	 ParamInMap_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_ParamInMap;
asn_struct_free_f ParamInMap_free;
asn_struct_print_f ParamInMap_print;
asn_constr_check_f ParamInMap_constraint;
ber_type_decoder_f ParamInMap_decode_ber;
der_type_encoder_f ParamInMap_encode_der;
xer_type_decoder_f ParamInMap_decode_xer;
xer_type_encoder_f ParamInMap_encode_xer;
oer_type_decoder_f ParamInMap_decode_oer;
oer_type_encoder_f ParamInMap_encode_oer;
per_type_decoder_f ParamInMap_decode_uper;
per_type_encoder_f ParamInMap_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ParamInMap_H_ */
#include <asn_internal.h>
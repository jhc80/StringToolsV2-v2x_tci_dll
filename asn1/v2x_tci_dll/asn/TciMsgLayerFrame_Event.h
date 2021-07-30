/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TciMsgLayerFrame_Event_H_
#define	_TciMsgLayerFrame_Event_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum TciMsgLayerFrame_Event {
	TciMsgLayerFrame_Event_eBsmRx	= 0,
	TciMsgLayerFrame_Event_eMapRx	= 1,
	TciMsgLayerFrame_Event_eRsmRx	= 2,
	TciMsgLayerFrame_Event_eSpatRx	= 3,
	TciMsgLayerFrame_Event_eRsiRx	= 4,
	TciMsgLayerFrame_Event_exceptionReport	= 5
} e_TciMsgLayerFrame_Event;

/* Event */
typedef long	 TciMsgLayerFrame_Event_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_TciMsgLayerFrame_Event_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_TciMsgLayerFrame_Event;
extern const asn_INTEGER_specifics_t asn_SPC_TciMsgLayerFrame_Event_specs_1;
asn_struct_free_f TciMsgLayerFrame_Event_free;
asn_struct_print_f TciMsgLayerFrame_Event_print;
asn_constr_check_f TciMsgLayerFrame_Event_constraint;
ber_type_decoder_f TciMsgLayerFrame_Event_decode_ber;
der_type_encoder_f TciMsgLayerFrame_Event_encode_der;
xer_type_decoder_f TciMsgLayerFrame_Event_decode_xer;
xer_type_encoder_f TciMsgLayerFrame_Event_encode_xer;
oer_type_decoder_f TciMsgLayerFrame_Event_decode_oer;
oer_type_encoder_f TciMsgLayerFrame_Event_encode_oer;
per_type_decoder_f TciMsgLayerFrame_Event_decode_uper;
per_type_encoder_f TciMsgLayerFrame_Event_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _TciMsgLayerFrame_Event_H_ */
#include <asn_internal.h>

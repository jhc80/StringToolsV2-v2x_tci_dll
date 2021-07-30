/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_MsgType_H_
#define	_MsgType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum MsgType {
	MsgType_bsmMsgType	= 0,
	MsgType_mapRelativePos	= 1,
	MsgType_mapAbsolutePos	= 2,
	MsgType_spatTimeCounting	= 3,
	MsgType_spatUTCTiming	= 4,
	MsgType_rsiMsgType	= 5,
	MsgType_rsmMsgType	= 6
} e_MsgType;

/* MsgType */
typedef long	 MsgType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_MsgType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_MsgType;
extern const asn_INTEGER_specifics_t asn_SPC_MsgType_specs_1;
asn_struct_free_f MsgType_free;
asn_struct_print_f MsgType_print;
asn_constr_check_f MsgType_constraint;
ber_type_decoder_f MsgType_decode_ber;
der_type_encoder_f MsgType_encode_der;
xer_type_decoder_f MsgType_decode_xer;
xer_type_encoder_f MsgType_encode_xer;
oer_type_decoder_f MsgType_decode_oer;
oer_type_encoder_f MsgType_encode_oer;
per_type_decoder_f MsgType_decode_uper;
per_type_encoder_f MsgType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _MsgType_H_ */
#include <asn_internal.h>

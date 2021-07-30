/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_BsmPduParam_H_
#define	_BsmPduParam_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum BsmPduParam {
	BsmPduParam_containsPosition3D	= 0,
	BsmPduParam_containsVehTransmissionState	= 1,
	BsmPduParam_containsVehSpeed	= 2,
	BsmPduParam_containsVehHeading	= 3,
	BsmPduParam_containsVehBrakeSystemStatus	= 4,
	BsmPduParam_containsVehSize	= 5,
	BsmPduParam_containsVehClassification	= 6,
	BsmPduParam_containsVehEventFlags	= 7,
	BsmPduParam_containsVehEmergencyExtensions	= 8
} e_BsmPduParam;

/* BsmPduParam */
typedef BIT_STRING_t	 BsmPduParam_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BsmPduParam;
asn_struct_free_f BsmPduParam_free;
asn_struct_print_f BsmPduParam_print;
asn_constr_check_f BsmPduParam_constraint;
ber_type_decoder_f BsmPduParam_decode_ber;
der_type_encoder_f BsmPduParam_encode_der;
xer_type_decoder_f BsmPduParam_decode_xer;
xer_type_encoder_f BsmPduParam_encode_xer;
oer_type_decoder_f BsmPduParam_decode_oer;
oer_type_encoder_f BsmPduParam_encode_oer;
per_type_decoder_f BsmPduParam_decode_uper;
per_type_encoder_f BsmPduParam_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _BsmPduParam_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "AcaEeCertResponseCubkSpdu"
 * 	found in "asn/AcaEeCertResponseCubkSpdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_EeRaCertRequestSpdu_H_
#define	_EeRaCertRequestSpdu_H_


#include <asn_application.h>

/* Including external dependencies */
#include "V2XSecData-SignedEncryptedCertRequest.h"

#ifdef __cplusplus
extern "C" {
#endif

/* EeRaCertRequestSpdu */
typedef V2XSecData_SignedEncryptedCertRequest_89P0_t	 EeRaCertRequestSpdu_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_EeRaCertRequestSpdu;
asn_struct_free_f EeRaCertRequestSpdu_free;
asn_struct_print_f EeRaCertRequestSpdu_print;
asn_constr_check_f EeRaCertRequestSpdu_constraint;
ber_type_decoder_f EeRaCertRequestSpdu_decode_ber;
der_type_encoder_f EeRaCertRequestSpdu_encode_der;
xer_type_decoder_f EeRaCertRequestSpdu_decode_xer;
xer_type_encoder_f EeRaCertRequestSpdu_encode_xer;
oer_type_decoder_f EeRaCertRequestSpdu_decode_oer;
oer_type_encoder_f EeRaCertRequestSpdu_encode_oer;
per_type_decoder_f EeRaCertRequestSpdu_decode_uper;
per_type_encoder_f EeRaCertRequestSpdu_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _EeRaCertRequestSpdu_H_ */
#include <asn_internal.h>

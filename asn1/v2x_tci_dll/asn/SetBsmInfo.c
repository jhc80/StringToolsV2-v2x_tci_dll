/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SetBsmInfo.h"

/*
 * This type is implemented using BsmInfo,
 * so here we adjust the DEF accordingly.
 */
static const ber_tlv_tag_t asn_DEF_SetBsmInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_TYPE_descriptor_t asn_DEF_SetBsmInfo = {
	"SetBsmInfo",
	"SetBsmInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_SetBsmInfo_tags_1,
	sizeof(asn_DEF_SetBsmInfo_tags_1)
		/sizeof(asn_DEF_SetBsmInfo_tags_1[0]), /* 1 */
	asn_DEF_SetBsmInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetBsmInfo_tags_1)
		/sizeof(asn_DEF_SetBsmInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_BsmInfo_1,
	9,	/* Elements count */
	&asn_SPC_BsmInfo_specs_1	/* Additional specs */
};

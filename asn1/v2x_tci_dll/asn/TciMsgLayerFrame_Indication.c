/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "TciMsgLayerFrame_Indication.h"

asn_TYPE_member_t asn_MBR_TciMsgLayerFrame_Indication_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TciMsgLayerFrame_Indication, event),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TciMsgLayerFrame_Event,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"event"
		},
	{ ATF_POINTER, 2, offsetof(struct TciMsgLayerFrame_Indication, msgLayerPduParam),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_MsgLayerPduParam,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"msgLayerPduParam"
		},
	{ ATF_POINTER, 1, offsetof(struct TciMsgLayerFrame_Indication, exceptionInfo),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TciMsgLayerFrame_Exception,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"exceptionInfo"
		},
};
static const int asn_MAP_TciMsgLayerFrame_Indication_oms_1[] = { 1, 2 };
static const ber_tlv_tag_t asn_DEF_TciMsgLayerFrame_Indication_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_TciMsgLayerFrame_Indication_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* event */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* msgLayerPduParam */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* exceptionInfo */
};
asn_SEQUENCE_specifics_t asn_SPC_TciMsgLayerFrame_Indication_specs_1 = {
	sizeof(struct TciMsgLayerFrame_Indication),
	offsetof(struct TciMsgLayerFrame_Indication, _asn_ctx),
	asn_MAP_TciMsgLayerFrame_Indication_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_TciMsgLayerFrame_Indication_oms_1,	/* Optional members */
	2, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_TciMsgLayerFrame_Indication = {
	"Indication",
	"Indication",
	&asn_OP_SEQUENCE,
	asn_DEF_TciMsgLayerFrame_Indication_tags_1,
	sizeof(asn_DEF_TciMsgLayerFrame_Indication_tags_1)
		/sizeof(asn_DEF_TciMsgLayerFrame_Indication_tags_1[0]), /* 1 */
	asn_DEF_TciMsgLayerFrame_Indication_tags_1,	/* Same as above */
	sizeof(asn_DEF_TciMsgLayerFrame_Indication_tags_1)
		/sizeof(asn_DEF_TciMsgLayerFrame_Indication_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_TciMsgLayerFrame_Indication_1,
	3,	/* Elements count */
	&asn_SPC_TciMsgLayerFrame_Indication_specs_1	/* Additional specs */
};


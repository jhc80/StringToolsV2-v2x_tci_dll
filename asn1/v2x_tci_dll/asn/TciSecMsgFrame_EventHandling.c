/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "TciSecMsgFrame_EventHandling.h"

asn_TYPE_member_t asn_MBR_TciSecMsgFrame_EventHandling_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_EventHandling, rxFlag),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TciSecMsgFrame_RxFlag,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rxFlag"
		},
};
static const ber_tlv_tag_t asn_DEF_TciSecMsgFrame_EventHandling_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_TciSecMsgFrame_EventHandling_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* rxFlag */
};
asn_SEQUENCE_specifics_t asn_SPC_TciSecMsgFrame_EventHandling_specs_1 = {
	sizeof(struct TciSecMsgFrame_EventHandling),
	offsetof(struct TciSecMsgFrame_EventHandling, _asn_ctx),
	asn_MAP_TciSecMsgFrame_EventHandling_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_EventHandling = {
	"EventHandling",
	"EventHandling",
	&asn_OP_SEQUENCE,
	asn_DEF_TciSecMsgFrame_EventHandling_tags_1,
	sizeof(asn_DEF_TciSecMsgFrame_EventHandling_tags_1)
		/sizeof(asn_DEF_TciSecMsgFrame_EventHandling_tags_1[0]), /* 1 */
	asn_DEF_TciSecMsgFrame_EventHandling_tags_1,	/* Same as above */
	sizeof(asn_DEF_TciSecMsgFrame_EventHandling_tags_1)
		/sizeof(asn_DEF_TciSecMsgFrame_EventHandling_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_TciSecMsgFrame_EventHandling_1,
	1,	/* Elements count */
	&asn_SPC_TciSecMsgFrame_EventHandling_specs_1	/* Additional specs */
};


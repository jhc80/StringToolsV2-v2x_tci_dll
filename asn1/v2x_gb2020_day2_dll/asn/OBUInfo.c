/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "OBUInfo.h"

asn_TYPE_member_t asn_MBR_OBUInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct OBUInfo, obuType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OBUType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"obuType"
		},
	{ ATF_POINTER, 1, offsetof(struct OBUInfo, obuMotionStatus),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OBUMotionStatus,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"obuMotionStatus"
		},
};
static const int asn_MAP_OBUInfo_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_OBUInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_OBUInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* obuType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* obuMotionStatus */
};
asn_SEQUENCE_specifics_t asn_SPC_OBUInfo_specs_1 = {
	sizeof(struct OBUInfo),
	offsetof(struct OBUInfo, _asn_ctx),
	asn_MAP_OBUInfo_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_OBUInfo_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_OBUInfo = {
	"OBUInfo",
	"OBUInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_OBUInfo_tags_1,
	sizeof(asn_DEF_OBUInfo_tags_1)
		/sizeof(asn_DEF_OBUInfo_tags_1[0]), /* 1 */
	asn_DEF_OBUInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_OBUInfo_tags_1)
		/sizeof(asn_DEF_OBUInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_OBUInfo_1,
	2,	/* Elements count */
	&asn_SPC_OBUInfo_specs_1	/* Additional specs */
};


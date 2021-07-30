/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "RxMapInfo.h"

asn_TYPE_member_t asn_MBR_RxMapInfo_1[] = {
	{ ATF_POINTER, 5, offsetof(struct RxMapInfo, basicMapNodesInfo),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BasicMapNodesInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"basicMapNodesInfo"
		},
	{ ATF_POINTER, 4, offsetof(struct RxMapInfo, basicMapLinkInfo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BasicMapLinkInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"basicMapLinkInfo"
		},
	{ ATF_POINTER, 3, offsetof(struct RxMapInfo, basicMapLaneInfo),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BasicMapLaneInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"basicMapLaneInfo"
		},
	{ ATF_POINTER, 2, offsetof(struct RxMapInfo, connectsToList),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConnectsToList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"connectsToList"
		},
	{ ATF_POINTER, 1, offsetof(struct RxMapInfo, allowedManeuvers),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AllowedManeuvers,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"allowedManeuvers"
		},
};
static const int asn_MAP_RxMapInfo_oms_1[] = { 0, 1, 2, 3, 4 };
static const ber_tlv_tag_t asn_DEF_RxMapInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RxMapInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* basicMapNodesInfo */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* basicMapLinkInfo */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* basicMapLaneInfo */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* connectsToList */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* allowedManeuvers */
};
asn_SEQUENCE_specifics_t asn_SPC_RxMapInfo_specs_1 = {
	sizeof(struct RxMapInfo),
	offsetof(struct RxMapInfo, _asn_ctx),
	asn_MAP_RxMapInfo_tag2el_1,
	5,	/* Count of tags in the map */
	asn_MAP_RxMapInfo_oms_1,	/* Optional members */
	5, 0,	/* Root/Additions */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RxMapInfo = {
	"RxMapInfo",
	"RxMapInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_RxMapInfo_tags_1,
	sizeof(asn_DEF_RxMapInfo_tags_1)
		/sizeof(asn_DEF_RxMapInfo_tags_1[0]), /* 1 */
	asn_DEF_RxMapInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_RxMapInfo_tags_1)
		/sizeof(asn_DEF_RxMapInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RxMapInfo_1,
	5,	/* Elements count */
	&asn_SPC_RxMapInfo_specs_1	/* Additional specs */
};


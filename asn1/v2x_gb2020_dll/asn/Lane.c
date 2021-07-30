/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MapLane"
 * 	found in "asn/MapLane.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "Lane.h"

asn_TYPE_member_t asn_MBR_Lane_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Lane, laneID),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaneID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"laneID"
		},
	{ ATF_POINTER, 6, offsetof(struct Lane, laneWidth),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaneWidth,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"laneWidth"
		},
	{ ATF_POINTER, 5, offsetof(struct Lane, laneAttributes),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaneAttributes,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"laneAttributes"
		},
	{ ATF_POINTER, 4, offsetof(struct Lane, maneuvers),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AllowedManeuvers,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"maneuvers"
		},
	{ ATF_POINTER, 3, offsetof(struct Lane, connectsTo),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ConnectsToList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"connectsTo"
		},
	{ ATF_POINTER, 2, offsetof(struct Lane, speedLimits),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpeedLimitList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"speedLimits"
		},
	{ ATF_POINTER, 1, offsetof(struct Lane, points),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PointList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"points"
		},
};
static const int asn_MAP_Lane_oms_1[] = { 1, 2, 3, 4, 5, 6 };
static const ber_tlv_tag_t asn_DEF_Lane_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Lane_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* laneID */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* laneWidth */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* laneAttributes */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* maneuvers */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* connectsTo */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* speedLimits */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* points */
};
asn_SEQUENCE_specifics_t asn_SPC_Lane_specs_1 = {
	sizeof(struct Lane),
	offsetof(struct Lane, _asn_ctx),
	asn_MAP_Lane_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_Lane_oms_1,	/* Optional members */
	6, 0,	/* Root/Additions */
	7,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_Lane = {
	"Lane",
	"Lane",
	&asn_OP_SEQUENCE,
	asn_DEF_Lane_tags_1,
	sizeof(asn_DEF_Lane_tags_1)
		/sizeof(asn_DEF_Lane_tags_1[0]), /* 1 */
	asn_DEF_Lane_tags_1,	/* Same as above */
	sizeof(asn_DEF_Lane_tags_1)
		/sizeof(asn_DEF_Lane_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_Lane_1,
	7,	/* Elements count */
	&asn_SPC_Lane_specs_1	/* Additional specs */
};


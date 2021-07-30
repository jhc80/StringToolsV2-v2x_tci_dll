/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSC"
 * 	found in "asn/RSC.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "DriveSuggestion.h"

asn_TYPE_member_t asn_MBR_DriveSuggestion_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DriveSuggestion, suggestion),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DriveBehavior,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"suggestion"
		},
	{ ATF_POINTER, 3, offsetof(struct DriveSuggestion, lifeTime),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeOffset,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"lifeTime"
		},
	{ ATF_POINTER, 2, offsetof(struct DriveSuggestion, relatedLink),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferenceLink,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"relatedLink"
		},
	{ ATF_POINTER, 1, offsetof(struct DriveSuggestion, relatedPath),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferencePath,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"relatedPath"
		},
};
static const int asn_MAP_DriveSuggestion_oms_1[] = { 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_DriveSuggestion_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_DriveSuggestion_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* suggestion */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* lifeTime */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* relatedLink */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* relatedPath */
};
asn_SEQUENCE_specifics_t asn_SPC_DriveSuggestion_specs_1 = {
	sizeof(struct DriveSuggestion),
	offsetof(struct DriveSuggestion, _asn_ctx),
	asn_MAP_DriveSuggestion_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_DriveSuggestion_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	4,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_DriveSuggestion = {
	"DriveSuggestion",
	"DriveSuggestion",
	&asn_OP_SEQUENCE,
	asn_DEF_DriveSuggestion_tags_1,
	sizeof(asn_DEF_DriveSuggestion_tags_1)
		/sizeof(asn_DEF_DriveSuggestion_tags_1[0]), /* 1 */
	asn_DEF_DriveSuggestion_tags_1,	/* Same as above */
	sizeof(asn_DEF_DriveSuggestion_tags_1)
		/sizeof(asn_DEF_DriveSuggestion_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_DriveSuggestion_1,
	4,	/* Elements count */
	&asn_SPC_DriveSuggestion_specs_1	/* Additional specs */
};


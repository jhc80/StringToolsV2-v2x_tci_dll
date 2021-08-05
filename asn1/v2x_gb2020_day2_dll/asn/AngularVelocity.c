/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "asn/SensorSharing.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "AngularVelocity.h"

asn_TYPE_member_t asn_MBR_AngularVelocity_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AngularVelocity, pitchRate),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PitchRate,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pitchRate"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AngularVelocity, rollRate),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RollRate,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rollRate"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AngularVelocity, yawRate),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_YawRate,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"yawRate"
		},
};
static const ber_tlv_tag_t asn_DEF_AngularVelocity_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AngularVelocity_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pitchRate */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* rollRate */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* yawRate */
};
asn_SEQUENCE_specifics_t asn_SPC_AngularVelocity_specs_1 = {
	sizeof(struct AngularVelocity),
	offsetof(struct AngularVelocity, _asn_ctx),
	asn_MAP_AngularVelocity_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_AngularVelocity = {
	"AngularVelocity",
	"AngularVelocity",
	&asn_OP_SEQUENCE,
	asn_DEF_AngularVelocity_tags_1,
	sizeof(asn_DEF_AngularVelocity_tags_1)
		/sizeof(asn_DEF_AngularVelocity_tags_1[0]), /* 1 */
	asn_DEF_AngularVelocity_tags_1,	/* Same as above */
	sizeof(asn_DEF_AngularVelocity_tags_1)
		/sizeof(asn_DEF_AngularVelocity_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_AngularVelocity_1,
	3,	/* Elements count */
	&asn_SPC_AngularVelocity_specs_1	/* Additional specs */
};

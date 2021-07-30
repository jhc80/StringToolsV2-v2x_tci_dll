/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "asn/SensorSharing.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "AttitudeConfidence.h"

asn_TYPE_member_t asn_MBR_AttitudeConfidence_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AttitudeConfidence, pitchConfidence),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HeadingConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pitchConfidence"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AttitudeConfidence, rollRateConfidence),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HeadingConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rollRateConfidence"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AttitudeConfidence, yawRate),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HeadingConfidence,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"yawRate"
		},
};
static const ber_tlv_tag_t asn_DEF_AttitudeConfidence_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AttitudeConfidence_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pitchConfidence */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* rollRateConfidence */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* yawRate */
};
asn_SEQUENCE_specifics_t asn_SPC_AttitudeConfidence_specs_1 = {
	sizeof(struct AttitudeConfidence),
	offsetof(struct AttitudeConfidence, _asn_ctx),
	asn_MAP_AttitudeConfidence_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_AttitudeConfidence = {
	"AttitudeConfidence",
	"AttitudeConfidence",
	&asn_OP_SEQUENCE,
	asn_DEF_AttitudeConfidence_tags_1,
	sizeof(asn_DEF_AttitudeConfidence_tags_1)
		/sizeof(asn_DEF_AttitudeConfidence_tags_1[0]), /* 1 */
	asn_DEF_AttitudeConfidence_tags_1,	/* Same as above */
	sizeof(asn_DEF_AttitudeConfidence_tags_1)
		/sizeof(asn_DEF_AttitudeConfidence_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_AttitudeConfidence_1,
	3,	/* Elements count */
	&asn_SPC_AttitudeConfidence_specs_1	/* Additional specs */
};


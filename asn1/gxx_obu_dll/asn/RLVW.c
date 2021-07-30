/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "RLVW.h"

asn_TYPE_member_t asn_MBR_RLVW_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RLVW, warnState),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_WarnState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"warnState"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RLVW, speedadvice),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpeedAdvice,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"speedadvice"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RLVW, light),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LightState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"light"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RLVW, timeCountDown),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeMark,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"timeCountDown"
		},
};
static const ber_tlv_tag_t asn_DEF_RLVW_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RLVW_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* warnState */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* speedadvice */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* light */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* timeCountDown */
};
asn_SEQUENCE_specifics_t asn_SPC_RLVW_specs_1 = {
	sizeof(struct RLVW),
	offsetof(struct RLVW, _asn_ctx),
	asn_MAP_RLVW_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RLVW = {
	"RLVW",
	"RLVW",
	&asn_OP_SEQUENCE,
	asn_DEF_RLVW_tags_1,
	sizeof(asn_DEF_RLVW_tags_1)
		/sizeof(asn_DEF_RLVW_tags_1[0]), /* 1 */
	asn_DEF_RLVW_tags_1,	/* Same as above */
	sizeof(asn_DEF_RLVW_tags_1)
		/sizeof(asn_DEF_RLVW_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RLVW_1,
	4,	/* Elements count */
	&asn_SPC_RLVW_specs_1	/* Additional specs */
};


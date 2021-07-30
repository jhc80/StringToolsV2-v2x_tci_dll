/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "CRLBaseTypes"
 * 	found in "asn/CRLBaseTypes.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "IMaxGroup.h"

asn_TYPE_member_t asn_MBR_IMaxGroup_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IMaxGroup, iMax),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"iMax"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IMaxGroup, contents),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SequenceOfIndividualRevocation,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"contents"
		},
	{ ATF_POINTER, 1, offsetof(struct IMaxGroup, singleSeeds),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SequenceOfLinkageSeed,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"singleSeeds"
		},
};
static const int asn_MAP_IMaxGroup_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_IMaxGroup_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_IMaxGroup_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* iMax */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* contents */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* singleSeeds */
};
asn_SEQUENCE_specifics_t asn_SPC_IMaxGroup_specs_1 = {
	sizeof(struct IMaxGroup),
	offsetof(struct IMaxGroup, _asn_ctx),
	asn_MAP_IMaxGroup_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_IMaxGroup_oms_1,	/* Optional members */
	0, 1,	/* Root/Additions */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_IMaxGroup = {
	"IMaxGroup",
	"IMaxGroup",
	&asn_OP_SEQUENCE,
	asn_DEF_IMaxGroup_tags_1,
	sizeof(asn_DEF_IMaxGroup_tags_1)
		/sizeof(asn_DEF_IMaxGroup_tags_1[0]), /* 1 */
	asn_DEF_IMaxGroup_tags_1,	/* Same as above */
	sizeof(asn_DEF_IMaxGroup_tags_1)
		/sizeof(asn_DEF_IMaxGroup_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_IMaxGroup_1,
	3,	/* Elements count */
	&asn_SPC_IMaxGroup_specs_1	/* Additional specs */
};


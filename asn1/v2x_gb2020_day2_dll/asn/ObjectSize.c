/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "asn/SensorSharing.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ObjectSize.h"

asn_TYPE_member_t asn_MBR_ObjectSize_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ObjectSize, width),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SizeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"width"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ObjectSize, length),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SizeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"length"
		},
	{ ATF_POINTER, 1, offsetof(struct ObjectSize, height),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SizeValue,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"height"
		},
};
static const int asn_MAP_ObjectSize_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_ObjectSize_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ObjectSize_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* width */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* length */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* height */
};
asn_SEQUENCE_specifics_t asn_SPC_ObjectSize_specs_1 = {
	sizeof(struct ObjectSize),
	offsetof(struct ObjectSize, _asn_ctx),
	asn_MAP_ObjectSize_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_ObjectSize_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ObjectSize = {
	"ObjectSize",
	"ObjectSize",
	&asn_OP_SEQUENCE,
	asn_DEF_ObjectSize_tags_1,
	sizeof(asn_DEF_ObjectSize_tags_1)
		/sizeof(asn_DEF_ObjectSize_tags_1[0]), /* 1 */
	asn_DEF_ObjectSize_tags_1,	/* Same as above */
	sizeof(asn_DEF_ObjectSize_tags_1)
		/sizeof(asn_DEF_ObjectSize_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ObjectSize_1,
	3,	/* Elements count */
	&asn_SPC_ObjectSize_specs_1	/* Additional specs */
};

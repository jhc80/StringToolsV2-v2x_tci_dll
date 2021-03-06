/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ToBeSignedCrl.h"

asn_TYPE_member_t asn_MBR_ToBeSignedCrl_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ToBeSignedCrl, crlSerial),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint32,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"crlSerial"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ToBeSignedCrl, issueDate),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Time32,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"issueDate"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ToBeSignedCrl, nextCrl),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Time32,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"nextCrl"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ToBeSignedCrl, entries),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SequenceOfRevokeInfo,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"entries"
		},
};
static const ber_tlv_tag_t asn_DEF_ToBeSignedCrl_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ToBeSignedCrl_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* crlSerial */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* issueDate */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* nextCrl */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* entries */
};
asn_SEQUENCE_specifics_t asn_SPC_ToBeSignedCrl_specs_1 = {
	sizeof(struct ToBeSignedCrl),
	offsetof(struct ToBeSignedCrl, _asn_ctx),
	asn_MAP_ToBeSignedCrl_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ToBeSignedCrl = {
	"ToBeSignedCrl",
	"ToBeSignedCrl",
	&asn_OP_SEQUENCE,
	asn_DEF_ToBeSignedCrl_tags_1,
	sizeof(asn_DEF_ToBeSignedCrl_tags_1)
		/sizeof(asn_DEF_ToBeSignedCrl_tags_1[0]), /* 1 */
	asn_DEF_ToBeSignedCrl_tags_1,	/* Same as above */
	sizeof(asn_DEF_ToBeSignedCrl_tags_1)
		/sizeof(asn_DEF_ToBeSignedCrl_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ToBeSignedCrl_1,
	4,	/* Elements count */
	&asn_SPC_ToBeSignedCrl_specs_1	/* Additional specs */
};


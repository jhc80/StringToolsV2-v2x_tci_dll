/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "Crl.h"

static asn_TYPE_member_t asn_MBR_Crl_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct Crl, version),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint8,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"version"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Crl, issuerId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_IssuerId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"issuerId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Crl, unsignedCrl),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ToBeSignedCrl,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"unsignedCrl"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct Crl, signature),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Signature,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"signature"
		},
};
static const ber_tlv_tag_t asn_DEF_Crl_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_Crl_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* version */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* issuerId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* unsignedCrl */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* signature */
};
static asn_SEQUENCE_specifics_t asn_SPC_Crl_specs_1 = {
	sizeof(struct Crl),
	offsetof(struct Crl, _asn_ctx),
	asn_MAP_Crl_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_Crl = {
	"Crl",
	"Crl",
	&asn_OP_SEQUENCE,
	asn_DEF_Crl_tags_1,
	sizeof(asn_DEF_Crl_tags_1)
		/sizeof(asn_DEF_Crl_tags_1[0]), /* 1 */
	asn_DEF_Crl_tags_1,	/* Same as above */
	sizeof(asn_DEF_Crl_tags_1)
		/sizeof(asn_DEF_Crl_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_Crl_1,
	4,	/* Elements count */
	&asn_SPC_Crl_specs_1	/* Additional specs */
};


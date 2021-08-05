/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LaRaInterfacePdu"
 * 	found in "asn/LaRaInterfacePdu.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "IndividualLVResponseLinkageChain.h"

static asn_TYPE_member_t asn_MBR_Member_4[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_EncryptedIndividualLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_Member_tags_4[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_Member_specs_4 = {
	sizeof(struct IndividualLVResponseLinkageChain__values__Member),
	offsetof(struct IndividualLVResponseLinkageChain__values__Member, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_Member_4 = {
	"SEQUENCE OF",
	"SEQUENCE_OF",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_Member_tags_4,
	sizeof(asn_DEF_Member_tags_4)
		/sizeof(asn_DEF_Member_tags_4[0]), /* 1 */
	asn_DEF_Member_tags_4,	/* Same as above */
	sizeof(asn_DEF_Member_tags_4)
		/sizeof(asn_DEF_Member_tags_4[0]), /* 1 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_Member_4,
	1,	/* Single element */
	&asn_SPC_Member_specs_4	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_values_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_Member_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_values_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_values_specs_3 = {
	sizeof(struct IndividualLVResponseLinkageChain__values),
	offsetof(struct IndividualLVResponseLinkageChain__values, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_values_3 = {
	"values",
	"values",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_values_tags_3,
	sizeof(asn_DEF_values_tags_3)
		/sizeof(asn_DEF_values_tags_3[0]) - 1, /* 1 */
	asn_DEF_values_tags_3,	/* Same as above */
	sizeof(asn_DEF_values_tags_3)
		/sizeof(asn_DEF_values_tags_3[0]), /* 2 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_values_3,
	1,	/* Single element */
	&asn_SPC_values_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_IndividualLVResponseLinkageChain_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IndividualLVResponseLinkageChain, jMax),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint8,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"jMax"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IndividualLVResponseLinkageChain, values),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_values_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"values"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IndividualLVResponseLinkageChain, linkageChainId),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LinkageChainId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"linkageChainId"
		},
};
static const ber_tlv_tag_t asn_DEF_IndividualLVResponseLinkageChain_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_IndividualLVResponseLinkageChain_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* jMax */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* values */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* linkageChainId */
};
asn_SEQUENCE_specifics_t asn_SPC_IndividualLVResponseLinkageChain_specs_1 = {
	sizeof(struct IndividualLVResponseLinkageChain),
	offsetof(struct IndividualLVResponseLinkageChain, _asn_ctx),
	asn_MAP_IndividualLVResponseLinkageChain_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_IndividualLVResponseLinkageChain = {
	"IndividualLVResponseLinkageChain",
	"IndividualLVResponseLinkageChain",
	&asn_OP_SEQUENCE,
	asn_DEF_IndividualLVResponseLinkageChain_tags_1,
	sizeof(asn_DEF_IndividualLVResponseLinkageChain_tags_1)
		/sizeof(asn_DEF_IndividualLVResponseLinkageChain_tags_1[0]), /* 1 */
	asn_DEF_IndividualLVResponseLinkageChain_tags_1,	/* Same as above */
	sizeof(asn_DEF_IndividualLVResponseLinkageChain_tags_1)
		/sizeof(asn_DEF_IndividualLVResponseLinkageChain_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_IndividualLVResponseLinkageChain_1,
	3,	/* Elements count */
	&asn_SPC_IndividualLVResponseLinkageChain_specs_1	/* Additional specs */
};

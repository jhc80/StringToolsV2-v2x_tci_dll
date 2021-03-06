/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "VIRQ.h"

asn_TYPE_member_t asn_MBR_VIRQ_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VIRQ, type),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BehaviorType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"type"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VIRQ, state),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RequestState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"state"
		},
};
static const ber_tlv_tag_t asn_DEF_VIRQ_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_VIRQ_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* type */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* state */
};
asn_SEQUENCE_specifics_t asn_SPC_VIRQ_specs_1 = {
	sizeof(struct VIRQ),
	offsetof(struct VIRQ, _asn_ctx),
	asn_MAP_VIRQ_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_VIRQ = {
	"VIRQ",
	"VIRQ",
	&asn_OP_SEQUENCE,
	asn_DEF_VIRQ_tags_1,
	sizeof(asn_DEF_VIRQ_tags_1)
		/sizeof(asn_DEF_VIRQ_tags_1[0]), /* 1 */
	asn_DEF_VIRQ_tags_1,	/* Same as above */
	sizeof(asn_DEF_VIRQ_tags_1)
		/sizeof(asn_DEF_VIRQ_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_VIRQ_1,
	2,	/* Elements count */
	&asn_SPC_VIRQ_specs_1	/* Additional specs */
};


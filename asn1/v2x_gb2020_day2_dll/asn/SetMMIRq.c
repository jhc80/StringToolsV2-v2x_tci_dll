/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SetMMIRq.h"

asn_TYPE_member_t asn_MBR_SetMMIRq_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetMMIRq, toll),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TollResult,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"toll"
		},
};
static const ber_tlv_tag_t asn_DEF_SetMMIRq_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SetMMIRq_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* toll */
};
asn_SEQUENCE_specifics_t asn_SPC_SetMMIRq_specs_1 = {
	sizeof(struct SetMMIRq),
	offsetof(struct SetMMIRq, _asn_ctx),
	asn_MAP_SetMMIRq_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SetMMIRq = {
	"SetMMIRq",
	"SetMMIRq",
	&asn_OP_SEQUENCE,
	asn_DEF_SetMMIRq_tags_1,
	sizeof(asn_DEF_SetMMIRq_tags_1)
		/sizeof(asn_DEF_SetMMIRq_tags_1[0]), /* 1 */
	asn_DEF_SetMMIRq_tags_1,	/* Same as above */
	sizeof(asn_DEF_SetMMIRq_tags_1)
		/sizeof(asn_DEF_SetMMIRq_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SetMMIRq_1,
	1,	/* Elements count */
	&asn_SPC_SetMMIRq_specs_1	/* Additional specs */
};

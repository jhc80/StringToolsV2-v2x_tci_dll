/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "RxSpatRequirement.h"

asn_TYPE_member_t asn_MBR_RxSpatRequirement_1[] = {
	{ ATF_POINTER, 1, offsetof(struct RxSpatRequirement, phaseId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhaseID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"phaseId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RxSpatRequirement, paramInSpat),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParamInSpat,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"paramInSpat"
		},
};
static const int asn_MAP_RxSpatRequirement_oms_1[] = { 0 };
static const ber_tlv_tag_t asn_DEF_RxSpatRequirement_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RxSpatRequirement_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* phaseId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* paramInSpat */
};
asn_SEQUENCE_specifics_t asn_SPC_RxSpatRequirement_specs_1 = {
	sizeof(struct RxSpatRequirement),
	offsetof(struct RxSpatRequirement, _asn_ctx),
	asn_MAP_RxSpatRequirement_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_RxSpatRequirement_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RxSpatRequirement = {
	"RxSpatRequirement",
	"RxSpatRequirement",
	&asn_OP_SEQUENCE,
	asn_DEF_RxSpatRequirement_tags_1,
	sizeof(asn_DEF_RxSpatRequirement_tags_1)
		/sizeof(asn_DEF_RxSpatRequirement_tags_1[0]), /* 1 */
	asn_DEF_RxSpatRequirement_tags_1,	/* Same as above */
	sizeof(asn_DEF_RxSpatRequirement_tags_1)
		/sizeof(asn_DEF_RxSpatRequirement_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RxSpatRequirement_1,
	2,	/* Elements count */
	&asn_SPC_RxSpatRequirement_specs_1	/* Additional specs */
};


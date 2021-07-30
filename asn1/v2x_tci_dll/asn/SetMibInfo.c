/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SetMibInfo.h"

static asn_oer_constraints_t asn_OER_type_SetMibInfo_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_SetMibInfo_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  0,  0,  0,  0 }	/* (0..0,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_SetMibInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SetMibInfo, choice.dsmMaxLength),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DsmMaxLength,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"dsmMaxLength"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_SetMibInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 } /* dsmMaxLength */
};
asn_CHOICE_specifics_t asn_SPC_SetMibInfo_specs_1 = {
	sizeof(struct SetMibInfo),
	offsetof(struct SetMibInfo, _asn_ctx),
	offsetof(struct SetMibInfo, present),
	sizeof(((struct SetMibInfo *)0)->present),
	asn_MAP_SetMibInfo_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0,
	1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_SetMibInfo = {
	"SetMibInfo",
	"SetMibInfo",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_SetMibInfo_constr_1, &asn_PER_type_SetMibInfo_constr_1, CHOICE_constraint },
	asn_MBR_SetMibInfo_1,
	1,	/* Elements count */
	&asn_SPC_SetMibInfo_specs_1	/* Additional specs */
};


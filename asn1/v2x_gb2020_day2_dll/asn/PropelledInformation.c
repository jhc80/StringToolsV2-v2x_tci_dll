/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PSM"
 * 	found in "asn/PSM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "PropelledInformation.h"

static asn_oer_constraints_t asn_OER_type_PropelledInformation_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_PropelledInformation_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  2,  2,  0,  2 }	/* (0..2,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_PropelledInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PropelledInformation, choice.human),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HumanPropelledType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"human"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PropelledInformation, choice.animal),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AnimalPropelledType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"animal"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PropelledInformation, choice.motor),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MotorizedPropelledType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"motor"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_PropelledInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* human */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* animal */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* motor */
};
asn_CHOICE_specifics_t asn_SPC_PropelledInformation_specs_1 = {
	sizeof(struct PropelledInformation),
	offsetof(struct PropelledInformation, _asn_ctx),
	offsetof(struct PropelledInformation, present),
	sizeof(((struct PropelledInformation *)0)->present),
	asn_MAP_PropelledInformation_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0,
	3	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_PropelledInformation = {
	"PropelledInformation",
	"PropelledInformation",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_PropelledInformation_constr_1, &asn_PER_type_PropelledInformation_constr_1, CHOICE_constraint },
	asn_MBR_PropelledInformation_1,
	3,	/* Elements count */
	&asn_SPC_PropelledInformation_specs_1	/* Additional specs */
};


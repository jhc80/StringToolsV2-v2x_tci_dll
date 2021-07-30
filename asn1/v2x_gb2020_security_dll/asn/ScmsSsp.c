/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ScmsSsp"
 * 	found in "asn/ScmsSsp.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ScmsSsp.h"

static asn_oer_constraints_t asn_OER_type_ScmsSsp_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_ScmsSsp_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  10 }	/* (0..10,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_ScmsSsp_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.root),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RootCaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"root"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.ma),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ma"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.pg),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PgSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pg"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.ica),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IcaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ica"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.eca),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EcaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"eca"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.cra),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CraSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cra"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.dcm),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DcmSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"dcm"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.aca),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AcaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"aca"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.la),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_LaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"la"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.ra),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RaSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ra"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScmsSsp, choice.ee),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EeSsp,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ee"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_ScmsSsp_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* root */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ma */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* pg */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* ica */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* eca */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* cra */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* dcm */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* aca */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* la */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* ra */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 } /* ee */
};
static asn_CHOICE_specifics_t asn_SPC_ScmsSsp_specs_1 = {
	sizeof(struct ScmsSsp),
	offsetof(struct ScmsSsp, _asn_ctx),
	offsetof(struct ScmsSsp, present),
	sizeof(((struct ScmsSsp *)0)->present),
	asn_MAP_ScmsSsp_tag2el_1,
	11,	/* Count of tags in the map */
	0, 0,
	11	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ScmsSsp = {
	"ScmsSsp",
	"ScmsSsp",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_ScmsSsp_constr_1, &asn_PER_type_ScmsSsp_constr_1, CHOICE_constraint },
	asn_MBR_ScmsSsp_1,
	11,	/* Elements count */
	&asn_SPC_ScmsSsp_specs_1	/* Additional specs */
};


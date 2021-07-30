/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSI"
 * 	found in "asn/RSI.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "RTSData.h"

static int
memb_rtsId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 255)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_rtsId_constr_2 CC_NOTUSED = {
	{ 1, 1 }	/* (0..255) */,
	-1};
static asn_per_constraints_t asn_PER_memb_rtsId_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  0,  255 }	/* (0..255) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_RTSData_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RTSData, rtsId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_rtsId_constr_2, &asn_PER_memb_rtsId_constr_2,  memb_rtsId_constraint_1 },
		0, 0, /* No default value */
		"rtsId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RTSData, signType),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SignType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"signType"
		},
	{ ATF_POINTER, 7, offsetof(struct RTSData, signPos),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionOffsetLLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"signPos"
		},
	{ ATF_POINTER, 6, offsetof(struct RTSData, description),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_Description,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"description"
		},
	{ ATF_POINTER, 5, offsetof(struct RTSData, timeDetails),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSITimeDetails,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"timeDetails"
		},
	{ ATF_POINTER, 4, offsetof(struct RTSData, priority),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSIPriority,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"priority"
		},
	{ ATF_POINTER, 3, offsetof(struct RTSData, referencePaths),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferencePathList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"referencePaths"
		},
	{ ATF_POINTER, 2, offsetof(struct RTSData, referenceLinks),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ReferenceLinkList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"referenceLinks"
		},
	{ ATF_POINTER, 1, offsetof(struct RTSData, auxiliarySign),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AuxiliarySign,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"auxiliarySign"
		},
};
static const int asn_MAP_RTSData_oms_1[] = { 2, 3, 4, 5, 6, 7, 8 };
static const ber_tlv_tag_t asn_DEF_RTSData_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RTSData_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* rtsId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* signType */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* signPos */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* description */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* timeDetails */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* priority */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* referencePaths */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* referenceLinks */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 } /* auxiliarySign */
};
asn_SEQUENCE_specifics_t asn_SPC_RTSData_specs_1 = {
	sizeof(struct RTSData),
	offsetof(struct RTSData, _asn_ctx),
	asn_MAP_RTSData_tag2el_1,
	9,	/* Count of tags in the map */
	asn_MAP_RTSData_oms_1,	/* Optional members */
	6, 1,	/* Root/Additions */
	8,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RTSData = {
	"RTSData",
	"RTSData",
	&asn_OP_SEQUENCE,
	asn_DEF_RTSData_tags_1,
	sizeof(asn_DEF_RTSData_tags_1)
		/sizeof(asn_DEF_RTSData_tags_1[0]), /* 1 */
	asn_DEF_RTSData_tags_1,	/* Same as above */
	sizeof(asn_DEF_RTSData_tags_1)
		/sizeof(asn_DEF_RTSData_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RTSData_1,
	9,	/* Elements count */
	&asn_SPC_RTSData_specs_1	/* Additional specs */
};


/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSI"
 * 	found in "asn/RSI.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "RoadSideInformation.h"

static int check_permitted_alphabet_7(const void *sptr) {
	/* The underlying type is IA5String */
	const IA5String_t *st = (const IA5String_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!(cv <= 127)) return -1;
	}
	return 0;
}

static int
memb_id_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 8)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_rsiId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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

static int
memb_description_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const IA5String_t *st = (const IA5String_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size >= 1 && size <= 256)
		 && !check_permitted_alphabet_7(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_id_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_id_constr_4 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_rsiId_constr_5 CC_NOTUSED = {
	{ 1, 1 }	/* (0..255) */,
	-1};
static asn_per_constraints_t asn_PER_memb_rsiId_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  0,  255 }	/* (0..255) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_description_constr_7 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..256)) */};
static asn_per_constraints_t asn_PER_memb_description_constr_7 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 7,  7,  0,  127 }	/* (0..127) */,
	{ APC_CONSTRAINED,	 8,  8,  1,  256 }	/* (SIZE(1..256)) */,
	0, 0	/* No PER character map necessary */
};
asn_TYPE_member_t asn_MBR_RoadSideInformation_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, msgCnt),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MsgCount,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"msgCnt"
		},
	{ ATF_POINTER, 1, offsetof(struct RoadSideInformation, timeStamp),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MinuteOfTheYear,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"timeStamp"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, id),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_id_constr_4, &asn_PER_memb_id_constr_4,  memb_id_constraint_1 },
		0, 0, /* No default value */
		"id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, rsiId),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_rsiId_constr_5, &asn_PER_memb_rsiId_constr_5,  memb_rsiId_constraint_1 },
		0, 0, /* No default value */
		"rsiId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, alertType),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AlertType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"alertType"
		},
	{ ATF_POINTER, 2, offsetof(struct RoadSideInformation, description),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_IA5String,
		0,
		{ &asn_OER_memb_description_constr_7, &asn_PER_memb_description_constr_7,  memb_description_constraint_1 },
		0, 0, /* No default value */
		"description"
		},
	{ ATF_POINTER, 1, offsetof(struct RoadSideInformation, priority),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Priority,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"priority"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, refPos),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Position3D,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"refPos"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, alertPath),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PathPointList,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"alertPath"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct RoadSideInformation, alertRadius),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Radius,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"alertRadius"
		},
};
static const int asn_MAP_RoadSideInformation_oms_1[] = { 1, 5, 6 };
static const ber_tlv_tag_t asn_DEF_RoadSideInformation_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RoadSideInformation_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* msgCnt */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* timeStamp */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* id */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* rsiId */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* alertType */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* description */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* priority */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* refPos */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* alertPath */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 } /* alertRadius */
};
asn_SEQUENCE_specifics_t asn_SPC_RoadSideInformation_specs_1 = {
	sizeof(struct RoadSideInformation),
	offsetof(struct RoadSideInformation, _asn_ctx),
	asn_MAP_RoadSideInformation_tag2el_1,
	10,	/* Count of tags in the map */
	asn_MAP_RoadSideInformation_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	10,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RoadSideInformation = {
	"RoadSideInformation",
	"RoadSideInformation",
	&asn_OP_SEQUENCE,
	asn_DEF_RoadSideInformation_tags_1,
	sizeof(asn_DEF_RoadSideInformation_tags_1)
		/sizeof(asn_DEF_RoadSideInformation_tags_1[0]), /* 1 */
	asn_DEF_RoadSideInformation_tags_1,	/* Same as above */
	sizeof(asn_DEF_RoadSideInformation_tags_1)
		/sizeof(asn_DEF_RoadSideInformation_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RoadSideInformation_1,
	10,	/* Elements count */
	&asn_SPC_RoadSideInformation_specs_1	/* Additional specs */
};

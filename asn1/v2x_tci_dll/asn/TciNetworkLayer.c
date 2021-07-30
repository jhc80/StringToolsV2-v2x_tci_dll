/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciNetworkLayerFrame"
 * 	found in "asn/net_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "TciNetworkLayer.h"

static const int permitted_alphabet_table_3[256] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/*                  */
 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	/* .                */
 2, 3, 4, 5, 6, 7, 8, 9,10,11, 0, 0, 0, 0, 0, 0,	/* 0123456789       */
};
static const int permitted_alphabet_code2value_3[11] = {
32,48,49,50,51,52,53,54,55,56,57,};


static int check_permitted_alphabet_3(const void *sptr) {
	const int *table = permitted_alphabet_table_3;
	/* The underlying type is NumericString */
	const NumericString_t *st = (const NumericString_t *)sptr;
	const uint8_t *ch = st->buf;
	const uint8_t *end = ch + st->size;
	
	for(; ch < end; ch++) {
		uint8_t cv = *ch;
		if(!table[cv]) return -1;
	}
	return 0;
}

static int
memb_version_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value == 2)) {
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
memb_msgNo_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const NumericString_t *st = (const NumericString_t *)sptr;
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size >= 10 && size <= 20)
		 && !check_permitted_alphabet_3(st)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int asn_PER_MAP_msgNo_3_v2c(unsigned int value) {
	if(value >= sizeof(permitted_alphabet_table_3)/sizeof(permitted_alphabet_table_3[0]))
		return -1;
	return permitted_alphabet_table_3[value] - 1;
}
static int asn_PER_MAP_msgNo_3_c2v(unsigned int code) {
	if(code >= sizeof(permitted_alphabet_code2value_3)/sizeof(permitted_alphabet_code2value_3[0]))
		return -1;
	return permitted_alphabet_code2value_3[code];
}
static asn_oer_constraints_t asn_OER_memb_version_constr_2 CC_NOTUSED = {
	{ 1, 1 }	/* (2..2) */,
	-1};
static asn_per_constraints_t asn_PER_memb_version_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  2,  2 }	/* (2..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_msgNo_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(10..20)) */};
static asn_per_constraints_t asn_PER_memb_msgNo_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  32,  57 }	/* (32..57) */,
	{ APC_CONSTRAINED,	 4,  4,  10,  20 }	/* (SIZE(10..20)) */,
	asn_PER_MAP_msgNo_3_v2c,	/* Value to PER code map */
	asn_PER_MAP_msgNo_3_c2v	/* PER code to value map */
};
static asn_TYPE_member_t asn_MBR_TciNetworkLayer_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TciNetworkLayer, version),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_version_constr_2, &asn_PER_memb_version_constr_2,  memb_version_constraint_1 },
		0, 0, /* No default value */
		"version"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciNetworkLayer, msgNo),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NumericString,
		0,
		{ &asn_OER_memb_msgNo_constr_3, &asn_PER_memb_msgNo_constr_3,  memb_msgNo_constraint_1 },
		0, 0, /* No default value */
		"msgNo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciNetworkLayer, msgFrame),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_TciNetworkLayerFrame_TciMsgFrame,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"msgFrame"
		},
};
static const ber_tlv_tag_t asn_DEF_TciNetworkLayer_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_TciNetworkLayer_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* version */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* msgNo */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* msgFrame */
};
static asn_SEQUENCE_specifics_t asn_SPC_TciNetworkLayer_specs_1 = {
	sizeof(struct TciNetworkLayer),
	offsetof(struct TciNetworkLayer, _asn_ctx),
	asn_MAP_TciNetworkLayer_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_TciNetworkLayer = {
	"TciNetworkLayer",
	"TciNetworkLayer",
	&asn_OP_SEQUENCE,
	asn_DEF_TciNetworkLayer_tags_1,
	sizeof(asn_DEF_TciNetworkLayer_tags_1)
		/sizeof(asn_DEF_TciNetworkLayer_tags_1[0]), /* 1 */
	asn_DEF_TciNetworkLayer_tags_1,	/* Same as above */
	sizeof(asn_DEF_TciNetworkLayer_tags_1)
		/sizeof(asn_DEF_TciNetworkLayer_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_TciNetworkLayer_1,
	3,	/* Elements count */
	&asn_SPC_TciNetworkLayer_specs_1	/* Additional specs */
};


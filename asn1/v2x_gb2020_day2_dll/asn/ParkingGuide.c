/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "asn/PAM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ParkingGuide.h"

static int
memb_vehId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_drivePath_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	size_t size;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	/* Determine the number of elements */
	size = _A_CSEQUENCE_FROM_VOID(sptr)->count;
	
	if((size >= 1 && size <= 32)) {
		/* Perform validation of the inner elements */
		return SEQUENCE_OF_constraint(td, sptr, ctfailcb, app_key);
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_targetParkingSlot_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 65535)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_type_drivePath_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_type_drivePath_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_vehId_constr_2 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_vehId_constr_2 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_drivePath_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(1..32)) */};
static asn_per_constraints_t asn_PER_memb_drivePath_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 5,  5,  1,  32 }	/* (SIZE(1..32)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_targetParkingSlot_constr_5 CC_NOTUSED = {
	{ 2, 1 }	/* (0..65535) */,
	-1};
static asn_per_constraints_t asn_PER_memb_targetParkingSlot_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 16,  16,  0,  65535 }	/* (0..65535) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_drivePath_3[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_PAMNodeID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_drivePath_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_drivePath_specs_3 = {
	sizeof(struct ParkingGuide__drivePath),
	offsetof(struct ParkingGuide__drivePath, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_drivePath_3 = {
	"drivePath",
	"drivePath",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_drivePath_tags_3,
	sizeof(asn_DEF_drivePath_tags_3)
		/sizeof(asn_DEF_drivePath_tags_3[0]) - 1, /* 1 */
	asn_DEF_drivePath_tags_3,	/* Same as above */
	sizeof(asn_DEF_drivePath_tags_3)
		/sizeof(asn_DEF_drivePath_tags_3[0]), /* 2 */
	{ &asn_OER_type_drivePath_constr_3, &asn_PER_type_drivePath_constr_3, SEQUENCE_OF_constraint },
	asn_MBR_drivePath_3,
	1,	/* Single element */
	&asn_SPC_drivePath_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ParkingGuide_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ParkingGuide, vehId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_vehId_constr_2, &asn_PER_memb_vehId_constr_2,  memb_vehId_constraint_1 },
		0, 0, /* No default value */
		"vehId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParkingGuide, drivePath),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_drivePath_3,
		0,
		{ &asn_OER_memb_drivePath_constr_3, &asn_PER_memb_drivePath_constr_3,  memb_drivePath_constraint_1 },
		0, 0, /* No default value */
		"drivePath"
		},
	{ ATF_POINTER, 1, offsetof(struct ParkingGuide, targetParkingSlot),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_targetParkingSlot_constr_5, &asn_PER_memb_targetParkingSlot_constr_5,  memb_targetParkingSlot_constraint_1 },
		0, 0, /* No default value */
		"targetParkingSlot"
		},
};
static const int asn_MAP_ParkingGuide_oms_1[] = { 2 };
static const ber_tlv_tag_t asn_DEF_ParkingGuide_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ParkingGuide_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* vehId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* drivePath */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* targetParkingSlot */
};
asn_SEQUENCE_specifics_t asn_SPC_ParkingGuide_specs_1 = {
	sizeof(struct ParkingGuide),
	offsetof(struct ParkingGuide, _asn_ctx),
	asn_MAP_ParkingGuide_tag2el_1,
	3,	/* Count of tags in the map */
	asn_MAP_ParkingGuide_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ParkingGuide = {
	"ParkingGuide",
	"ParkingGuide",
	&asn_OP_SEQUENCE,
	asn_DEF_ParkingGuide_tags_1,
	sizeof(asn_DEF_ParkingGuide_tags_1)
		/sizeof(asn_DEF_ParkingGuide_tags_1[0]), /* 1 */
	asn_DEF_ParkingGuide_tags_1,	/* Same as above */
	sizeof(asn_DEF_ParkingGuide_tags_1)
		/sizeof(asn_DEF_ParkingGuide_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ParkingGuide_1,
	3,	/* Elements count */
	&asn_SPC_ParkingGuide_specs_1	/* Additional specs */
};

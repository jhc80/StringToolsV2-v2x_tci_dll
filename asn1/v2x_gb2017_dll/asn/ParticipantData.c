/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "RSM"
 * 	found in "asn/RSM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ParticipantData.h"

static int
memb_ptcId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
memb_plateNo_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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
	
	if((size >= 4 && size <= 16)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_ptcId_constr_3 CC_NOTUSED = {
	{ 2, 1 }	/* (0..65535) */,
	-1};
static asn_per_constraints_t asn_PER_memb_ptcId_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 16,  16,  0,  65535 }	/* (0..65535) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_id_constr_5 CC_NOTUSED = {
	{ 0, 0 },
	8	/* (SIZE(8..8)) */};
static asn_per_constraints_t asn_PER_memb_id_constr_5 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 0,  0,  8,  8 }	/* (SIZE(8..8)) */,
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_plateNo_constr_6 CC_NOTUSED = {
	{ 0, 0 },
	-1	/* (SIZE(4..16)) */};
static asn_per_constraints_t asn_PER_memb_plateNo_constr_6 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_CONSTRAINED,	 4,  4,  4,  16 }	/* (SIZE(4..16)) */,
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ParticipantData_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, ptcType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ParticipantType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ptcType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, ptcId),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_ptcId_constr_3, &asn_PER_memb_ptcId_constr_3,  memb_ptcId_constraint_1 },
		0, 0, /* No default value */
		"ptcId"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, source),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SourceType,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"source"
		},
	{ ATF_POINTER, 2, offsetof(struct ParticipantData, id),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_id_constr_5, &asn_PER_memb_id_constr_5,  memb_id_constraint_1 },
		0, 0, /* No default value */
		"id"
		},
	{ ATF_POINTER, 1, offsetof(struct ParticipantData, plateNo),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		0,
		{ &asn_OER_memb_plateNo_constr_6, &asn_PER_memb_plateNo_constr_6,  memb_plateNo_constraint_1 },
		0, 0, /* No default value */
		"plateNo"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, secMark),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DSecond,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"secMark"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, pos),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionOffsetLLV,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pos"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, accuracy),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionConfidenceSet,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"accuracy"
		},
	{ ATF_POINTER, 1, offsetof(struct ParticipantData, transmission),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TransmissionState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"transmission"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, speed),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Speed,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"speed"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, heading),
		(ASN_TAG_CLASS_CONTEXT | (10 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Heading,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"heading"
		},
	{ ATF_POINTER, 3, offsetof(struct ParticipantData, angle),
		(ASN_TAG_CLASS_CONTEXT | (11 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SteeringWheelAngle,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"angle"
		},
	{ ATF_POINTER, 2, offsetof(struct ParticipantData, motionCfd),
		(ASN_TAG_CLASS_CONTEXT | (12 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_MotionConfidenceSet,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"motionCfd"
		},
	{ ATF_POINTER, 1, offsetof(struct ParticipantData, accelSet),
		(ASN_TAG_CLASS_CONTEXT | (13 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AccelerationSet4Way,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"accelSet"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ParticipantData, size),
		(ASN_TAG_CLASS_CONTEXT | (14 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VehicleSize,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"size"
		},
	{ ATF_POINTER, 1, offsetof(struct ParticipantData, vehicleClass),
		(ASN_TAG_CLASS_CONTEXT | (15 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_VehicleClassification,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"vehicleClass"
		},
};
static const int asn_MAP_ParticipantData_oms_1[] = { 3, 4, 8, 11, 12, 13, 15 };
static const ber_tlv_tag_t asn_DEF_ParticipantData_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ParticipantData_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ptcType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ptcId */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* source */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* id */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* plateNo */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* secMark */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* pos */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* accuracy */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* transmission */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 }, /* speed */
    { (ASN_TAG_CLASS_CONTEXT | (10 << 2)), 10, 0, 0 }, /* heading */
    { (ASN_TAG_CLASS_CONTEXT | (11 << 2)), 11, 0, 0 }, /* angle */
    { (ASN_TAG_CLASS_CONTEXT | (12 << 2)), 12, 0, 0 }, /* motionCfd */
    { (ASN_TAG_CLASS_CONTEXT | (13 << 2)), 13, 0, 0 }, /* accelSet */
    { (ASN_TAG_CLASS_CONTEXT | (14 << 2)), 14, 0, 0 }, /* size */
    { (ASN_TAG_CLASS_CONTEXT | (15 << 2)), 15, 0, 0 } /* vehicleClass */
};
asn_SEQUENCE_specifics_t asn_SPC_ParticipantData_specs_1 = {
	sizeof(struct ParticipantData),
	offsetof(struct ParticipantData, _asn_ctx),
	asn_MAP_ParticipantData_tag2el_1,
	16,	/* Count of tags in the map */
	asn_MAP_ParticipantData_oms_1,	/* Optional members */
	7, 0,	/* Root/Additions */
	16,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ParticipantData = {
	"ParticipantData",
	"ParticipantData",
	&asn_OP_SEQUENCE,
	asn_DEF_ParticipantData_tags_1,
	sizeof(asn_DEF_ParticipantData_tags_1)
		/sizeof(asn_DEF_ParticipantData_tags_1[0]), /* 1 */
	asn_DEF_ParticipantData_tags_1,	/* Same as above */
	sizeof(asn_DEF_ParticipantData_tags_1)
		/sizeof(asn_DEF_ParticipantData_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ParticipantData_1,
	16,	/* Elements count */
	&asn_SPC_ParticipantData_specs_1	/* Additional specs */
};


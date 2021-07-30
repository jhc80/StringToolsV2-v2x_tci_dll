/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "MsgDayII"
 * 	found in "asn/MsgDayII.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "MessageFrameExt.h"

static const long asn_VAL_1_testData = 0;
static const long asn_VAL_2_rtcmData = 10;
static const long asn_VAL_3_pamData = 14;
static const long asn_VAL_4_clpmmData = 16;
static const long asn_VAL_5_psmData = 15;
static const long asn_VAL_6_rscData = 11;
static const long asn_VAL_7_ssmData = 12;
static const long asn_VAL_8_virData = 13;
static const long asn_VAL_9_vpmData = 17;
static const asn_ioc_cell_t asn_IOS_MessageTypes_1_rows[] = {
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_1_testData },
	{ "&Type", aioc__type, &asn_DEF_TestMsg },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_2_rtcmData },
	{ "&Type", aioc__type, &asn_DEF_RTCMcorrections },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_3_pamData },
	{ "&Type", aioc__type, &asn_DEF_PAMData },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_4_clpmmData },
	{ "&Type", aioc__type, &asn_DEF_CLPMM },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_5_psmData },
	{ "&Type", aioc__type, &asn_DEF_PersonalSafetyMessage },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_6_rscData },
	{ "&Type", aioc__type, &asn_DEF_RoadsideCoordination },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_7_ssmData },
	{ "&Type", aioc__type, &asn_DEF_SensorSharingMsg },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_8_virData },
	{ "&Type", aioc__type, &asn_DEF_VehIntentionAndRequest },
	{ "&id", aioc__value, &asn_DEF_ExtMsgID, &asn_VAL_9_vpmData },
	{ "&Type", aioc__type, &asn_DEF_VehiclePaymentMessage }
};
static const asn_ioc_set_t asn_IOS_MessageTypes_1[] = {
	9, 2, asn_IOS_MessageTypes_1_rows
};
static int
memb_messageId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 32767)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_type_selector_result_t
select_MessageFrameExt_value_type(const asn_TYPE_descriptor_t *parent_type, const void *parent_sptr) {
	asn_type_selector_result_t result = {0, 0};
	const asn_ioc_set_t *itable = asn_IOS_MessageTypes_1;
	size_t constraining_column = 0; /* &id */
	size_t for_column = 1; /* &Type */
	size_t row;
	const long *constraining_value = (const long *)((const char *)parent_sptr + offsetof(struct MessageFrameExt, messageId));
	
	for(row=0; row < itable->rows_count; row++) {
	    const asn_ioc_cell_t *constraining_cell = &itable->rows[row * itable->columns_count + constraining_column];
	    const asn_ioc_cell_t *type_cell = &itable->rows[row * itable->columns_count + for_column];
	
	    if(constraining_cell->type_descriptor->op->compare_struct(constraining_cell->type_descriptor, constraining_value, constraining_cell->value_sptr) == 0) {
	        result.type_descriptor = type_cell->type_descriptor;
	        result.presence_index = row + 1;
	        break;
	    }
	}
	
	return result;
}

static int
memb_value_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	
	if(1 /* No applicable constraints whatsoever */) {
		/* Nothing is here. See below */
	}
	
	return td->encoding_constraints.general_constraints(td, sptr, ctfailcb, app_key);
}

static asn_oer_constraints_t asn_OER_memb_messageId_constr_2 CC_NOTUSED = {
	{ 2, 1 }	/* (0..32767) */,
	-1};
static asn_per_constraints_t asn_PER_memb_messageId_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 15,  15,  0,  32767 }	/* (0..32767) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_value_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_memb_value_constr_3 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_value_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.TestMsg),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_TestMsg,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"TestMsg"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.RTCMcorrections),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_RTCMcorrections,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"RTCMcorrections"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.PAMData),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_PAMData,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"PAMData"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.CLPMM),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_CLPMM,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"CLPMM"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.PersonalSafetyMessage),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_PersonalSafetyMessage,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"PersonalSafetyMessage"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.RoadsideCoordination),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_RoadsideCoordination,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"RoadsideCoordination"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.SensorSharingMsg),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_SensorSharingMsg,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"SensorSharingMsg"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.VehIntentionAndRequest),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_VehIntentionAndRequest,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"VehIntentionAndRequest"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt__value, choice.VehiclePaymentMessage),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_VehiclePaymentMessage,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"VehiclePaymentMessage"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_value_tag2el_3[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 0, 0, 8 }, /* TestMsg */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 1, -1, 7 }, /* RTCMcorrections */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 2, -2, 6 }, /* PAMData */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, -3, 5 }, /* CLPMM */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 4, -4, 4 }, /* PersonalSafetyMessage */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 5, -5, 3 }, /* RoadsideCoordination */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 6, -6, 2 }, /* SensorSharingMsg */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 7, -7, 1 }, /* VehIntentionAndRequest */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 8, -8, 0 } /* VehiclePaymentMessage */
};
static asn_CHOICE_specifics_t asn_SPC_value_specs_3 = {
	sizeof(struct MessageFrameExt__value),
	offsetof(struct MessageFrameExt__value, _asn_ctx),
	offsetof(struct MessageFrameExt__value, present),
	sizeof(((struct MessageFrameExt__value *)0)->present),
	asn_MAP_value_tag2el_3,
	9,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_value_3 = {
	"value",
	"value",
	&asn_OP_OPEN_TYPE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, 0, OPEN_TYPE_constraint },
	asn_MBR_value_3,
	9,	/* Elements count */
	&asn_SPC_value_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MessageFrameExt_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt, messageId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ExtMsgID,
		0,
		{ &asn_OER_memb_messageId_constr_2, &asn_PER_memb_messageId_constr_2,  memb_messageId_constraint_1 },
		0, 0, /* No default value */
		"messageId"
		},
	{ ATF_OPEN_TYPE | ATF_NOFLAGS, 0, offsetof(struct MessageFrameExt, value),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_value_3,
		select_MessageFrameExt_value_type,
		{ &asn_OER_memb_value_constr_3, &asn_PER_memb_value_constr_3,  memb_value_constraint_1 },
		0, 0, /* No default value */
		"value"
		},
};
static const ber_tlv_tag_t asn_DEF_MessageFrameExt_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MessageFrameExt_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* messageId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* value */
};
asn_SEQUENCE_specifics_t asn_SPC_MessageFrameExt_specs_1 = {
	sizeof(struct MessageFrameExt),
	offsetof(struct MessageFrameExt, _asn_ctx),
	asn_MAP_MessageFrameExt_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MessageFrameExt = {
	"MessageFrameExt",
	"MessageFrameExt",
	&asn_OP_SEQUENCE,
	asn_DEF_MessageFrameExt_tags_1,
	sizeof(asn_DEF_MessageFrameExt_tags_1)
		/sizeof(asn_DEF_MessageFrameExt_tags_1[0]), /* 1 */
	asn_DEF_MessageFrameExt_tags_1,	/* Same as above */
	sizeof(asn_DEF_MessageFrameExt_tags_1)
		/sizeof(asn_DEF_MessageFrameExt_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MessageFrameExt_1,
	2,	/* Elements count */
	&asn_SPC_MessageFrameExt_specs_1	/* Additional specs */
};


/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "TciSecMsgFrame_Request.h"

static const long asn_VAL_1_setInitialState = 0;
static const long asn_VAL_2_startSpduTx = 1;
static const long asn_VAL_3_stopSpduTx = 2;
static const long asn_VAL_4_startSpduRx = 3;
static const long asn_VAL_5_stopSpduRx = 4;
static const asn_ioc_cell_t asn_IOS_TciSecMsgFrame_MessageTypes_1_rows[] = {
	{ "&id", aioc__value, &asn_DEF_TciSecMsgFrame_MsgID, &asn_VAL_1_setInitialState },
	{ "&Type", aioc__type, &asn_DEF_TciSecMsgFrame_SetInitialState },
	{ "&id", aioc__value, &asn_DEF_TciSecMsgFrame_MsgID, &asn_VAL_2_startSpduTx },
	{ "&Type", aioc__type, &asn_DEF_StartSpduTx },
	{ "&id", aioc__value, &asn_DEF_TciSecMsgFrame_MsgID, &asn_VAL_3_stopSpduTx },
	{ "&Type", aioc__type, &asn_DEF_StopSpduTx },
	{ "&id", aioc__value, &asn_DEF_TciSecMsgFrame_MsgID, &asn_VAL_4_startSpduRx },
	{ "&Type", aioc__type, &asn_DEF_StartSpduRx },
	{ "&id", aioc__value, &asn_DEF_TciSecMsgFrame_MsgID, &asn_VAL_5_stopSpduRx },
	{ "&Type", aioc__type, &asn_DEF_StopSpduRx }
};
static const asn_ioc_set_t asn_IOS_TciSecMsgFrame_MessageTypes_1[] = {
	5, 2, asn_IOS_TciSecMsgFrame_MessageTypes_1_rows
};
static int
memb_msgId_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
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

static asn_type_selector_result_t
select_TciSecMsgFrame_Request_value_type(const asn_TYPE_descriptor_t *parent_type, const void *parent_sptr) {
	asn_type_selector_result_t result = {0, 0};
	const asn_ioc_set_t *itable = asn_IOS_TciSecMsgFrame_MessageTypes_1;
	size_t constraining_column = 0; /* &id */
	size_t for_column = 1; /* &Type */
	size_t row;
	const long *constraining_value = (const long *)((const char *)parent_sptr + offsetof(struct TciSecMsgFrame_Request, msgId));
	
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

static asn_oer_constraints_t asn_OER_memb_msgId_constr_2 CC_NOTUSED = {
	{ 1, 1 }	/* (0..255) */,
	-1};
static asn_per_constraints_t asn_PER_memb_msgId_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 8,  8,  0,  255 }	/* (0..255) */,
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
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request__value, choice.SetInitialState),
		(ASN_TAG_CLASS_UNIVERSAL | (1 << 2)),
		0,
		&asn_DEF_TciSecMsgFrame_SetInitialState,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"SetInitialState"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request__value, choice.StartSpduTx),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_StartSpduTx,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"StartSpduTx"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request__value, choice.StopSpduTx),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_StopSpduTx,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"StopSpduTx"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request__value, choice.StartSpduRx),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_StartSpduRx,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"StartSpduRx"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request__value, choice.StopSpduRx),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_StopSpduRx,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"StopSpduRx"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_value_tag2el_3[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (1 << 2)), 0, 0, 0 }, /* SetInitialState */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 1, 0, 3 }, /* StartSpduTx */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 2, -1, 2 }, /* StopSpduTx */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, -2, 1 }, /* StartSpduRx */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 4, -3, 0 } /* StopSpduRx */
};
static asn_CHOICE_specifics_t asn_SPC_value_specs_3 = {
	sizeof(struct TciSecMsgFrame_Request__value),
	offsetof(struct TciSecMsgFrame_Request__value, _asn_ctx),
	offsetof(struct TciSecMsgFrame_Request__value, present),
	sizeof(((struct TciSecMsgFrame_Request__value *)0)->present),
	asn_MAP_value_tag2el_3,
	5,	/* Count of tags in the map */
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
	5,	/* Elements count */
	&asn_SPC_value_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_TciSecMsgFrame_Request_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request, msgId),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TciSecMsgFrame_MsgID,
		0,
		{ &asn_OER_memb_msgId_constr_2, &asn_PER_memb_msgId_constr_2,  memb_msgId_constraint_1 },
		0, 0, /* No default value */
		"msgId"
		},
	{ ATF_OPEN_TYPE | ATF_NOFLAGS, 0, offsetof(struct TciSecMsgFrame_Request, value),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_value_3,
		select_TciSecMsgFrame_Request_value_type,
		{ &asn_OER_memb_value_constr_3, &asn_PER_memb_value_constr_3,  memb_value_constraint_1 },
		0, 0, /* No default value */
		"value"
		},
};
static const ber_tlv_tag_t asn_DEF_TciSecMsgFrame_Request_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_TciSecMsgFrame_Request_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* msgId */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* value */
};
asn_SEQUENCE_specifics_t asn_SPC_TciSecMsgFrame_Request_specs_1 = {
	sizeof(struct TciSecMsgFrame_Request),
	offsetof(struct TciSecMsgFrame_Request, _asn_ctx),
	asn_MAP_TciSecMsgFrame_Request_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_TciSecMsgFrame_Request = {
	"Request",
	"Request",
	&asn_OP_SEQUENCE,
	asn_DEF_TciSecMsgFrame_Request_tags_1,
	sizeof(asn_DEF_TciSecMsgFrame_Request_tags_1)
		/sizeof(asn_DEF_TciSecMsgFrame_Request_tags_1[0]), /* 1 */
	asn_DEF_TciSecMsgFrame_Request_tags_1,	/* Same as above */
	sizeof(asn_DEF_TciSecMsgFrame_Request_tags_1)
		/sizeof(asn_DEF_TciSecMsgFrame_Request_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_TciSecMsgFrame_Request_1,
	2,	/* Elements count */
	&asn_SPC_TciSecMsgFrame_Request_specs_1	/* Additional specs */
};

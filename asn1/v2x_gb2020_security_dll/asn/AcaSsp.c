/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "ScmsSsp"
 * 	found in "asn/ScmsSsp.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "AcaSsp.h"

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
	
	if((value == 1)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_version_constr_2 CC_NOTUSED = {
	{ 1, 1 }	/* (1..1) */,
	-1};
static asn_per_constraints_t asn_PER_memb_version_constr_2 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 0,  0,  1,  1 }	/* (1..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_AcaSsp_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AcaSsp, version),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint8,
		0,
		{ &asn_OER_memb_version_constr_2, &asn_PER_memb_version_constr_2,  memb_version_constraint_1 },
		0, 0, /* No default value */
		"version"
		},
};
static const ber_tlv_tag_t asn_DEF_AcaSsp_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_AcaSsp_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 } /* version */
};
asn_SEQUENCE_specifics_t asn_SPC_AcaSsp_specs_1 = {
	sizeof(struct AcaSsp),
	offsetof(struct AcaSsp, _asn_ctx),
	asn_MAP_AcaSsp_tag2el_1,
	1,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_AcaSsp = {
	"AcaSsp",
	"AcaSsp",
	&asn_OP_SEQUENCE,
	asn_DEF_AcaSsp_tags_1,
	sizeof(asn_DEF_AcaSsp_tags_1)
		/sizeof(asn_DEF_AcaSsp_tags_1[0]), /* 1 */
	asn_DEF_AcaSsp_tags_1,	/* Same as above */
	sizeof(asn_DEF_AcaSsp_tags_1)
		/sizeof(asn_DEF_AcaSsp_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_AcaSsp_1,
	1,	/* Elements count */
	&asn_SPC_AcaSsp_specs_1	/* Additional specs */
};


/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "EnrollmentCertResp.h"

int
EnrollmentCertResp_constraint(const asn_TYPE_descriptor_t *td, const void *sptr,
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

/*
 * This type is implemented using SecureMessage,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_EnrollmentCertResp_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_EnrollmentCertResp_constr_1 CC_NOTUSED = {
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const ber_tlv_tag_t asn_DEF_EnrollmentCertResp_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_TYPE_descriptor_t asn_DEF_EnrollmentCertResp = {
	"EnrollmentCertResp",
	"EnrollmentCertResp",
	&asn_OP_SEQUENCE,
	asn_DEF_EnrollmentCertResp_tags_1,
	sizeof(asn_DEF_EnrollmentCertResp_tags_1)
		/sizeof(asn_DEF_EnrollmentCertResp_tags_1[0]), /* 1 */
	asn_DEF_EnrollmentCertResp_tags_1,	/* Same as above */
	sizeof(asn_DEF_EnrollmentCertResp_tags_1)
		/sizeof(asn_DEF_EnrollmentCertResp_tags_1[0]), /* 1 */
	{ &asn_OER_type_EnrollmentCertResp_constr_1, &asn_PER_type_EnrollmentCertResp_constr_1, EnrollmentCertResp_constraint },
	asn_MBR_SecureMessage_1,
	2,	/* Elements count */
	&asn_SPC_SecureMessage_specs_1	/* Additional specs */
};


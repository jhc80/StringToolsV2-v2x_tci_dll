/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SecureMessage.h"

asn_TYPE_member_t asn_MBR_SecureMessage_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct SecureMessage, version),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Uint8,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"version"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct SecureMessage, payload),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_Payload,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"payload"
		},
};
static const ber_tlv_tag_t asn_DEF_SecureMessage_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_SecureMessage_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* version */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* payload */
};
asn_SEQUENCE_specifics_t asn_SPC_SecureMessage_specs_1 = {
	sizeof(struct SecureMessage),
	offsetof(struct SecureMessage, _asn_ctx),
	asn_MAP_SecureMessage_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_SecureMessage = {
	"SecureMessage",
	"SecureMessage",
	&asn_OP_SEQUENCE,
	asn_DEF_SecureMessage_tags_1,
	sizeof(asn_DEF_SecureMessage_tags_1)
		/sizeof(asn_DEF_SecureMessage_tags_1[0]), /* 1 */
	asn_DEF_SecureMessage_tags_1,	/* Same as above */
	sizeof(asn_DEF_SecureMessage_tags_1)
		/sizeof(asn_DEF_SecureMessage_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_SecureMessage_1,
	2,	/* Elements count */
	&asn_SPC_SecureMessage_specs_1	/* Additional specs */
};


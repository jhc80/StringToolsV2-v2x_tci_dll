/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "VehEmergencyExtensions.h"

asn_TYPE_member_t asn_MBR_VehEmergencyExtensions_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct VehEmergencyExtensions, responseType),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"responseType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VehEmergencyExtensions, sirenInUse),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"sirenInUse"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct VehEmergencyExtensions, lightbarInUse),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BIT_STRING,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"lightbarInUse"
		},
};
static const ber_tlv_tag_t asn_DEF_VehEmergencyExtensions_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_VehEmergencyExtensions_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* responseType */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* sirenInUse */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* lightbarInUse */
};
asn_SEQUENCE_specifics_t asn_SPC_VehEmergencyExtensions_specs_1 = {
	sizeof(struct VehEmergencyExtensions),
	offsetof(struct VehEmergencyExtensions, _asn_ctx),
	asn_MAP_VehEmergencyExtensions_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_VehEmergencyExtensions = {
	"VehEmergencyExtensions",
	"VehEmergencyExtensions",
	&asn_OP_SEQUENCE,
	asn_DEF_VehEmergencyExtensions_tags_1,
	sizeof(asn_DEF_VehEmergencyExtensions_tags_1)
		/sizeof(asn_DEF_VehEmergencyExtensions_tags_1[0]), /* 1 */
	asn_DEF_VehEmergencyExtensions_tags_1,	/* Same as above */
	sizeof(asn_DEF_VehEmergencyExtensions_tags_1)
		/sizeof(asn_DEF_VehEmergencyExtensions_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_VehEmergencyExtensions_1,
	3,	/* Elements count */
	&asn_SPC_VehEmergencyExtensions_specs_1	/* Additional specs */
};


/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "HeaderInfo.h"

asn_TYPE_member_t asn_MBR_HeaderInfo_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct HeaderInfo, itsAid),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"itsAid"
		},
	{ ATF_POINTER, 6, offsetof(struct HeaderInfo, hashAlg),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HashAlgorithm,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"hashAlg"
		},
	{ ATF_POINTER, 5, offsetof(struct HeaderInfo, genTime),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Time64,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"genTime"
		},
	{ ATF_POINTER, 4, offsetof(struct HeaderInfo, expiryTime),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Time64,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"expiryTime"
		},
	{ ATF_POINTER, 3, offsetof(struct HeaderInfo, location),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ThreeDLocation,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"location"
		},
	{ ATF_POINTER, 2, offsetof(struct HeaderInfo, digest),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_HashedId3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"digest"
		},
	{ ATF_POINTER, 1, offsetof(struct HeaderInfo, encKey),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PublicEncryptionKey,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"encKey"
		},
};
static const int asn_MAP_HeaderInfo_oms_1[] = { 1, 2, 3, 4, 5, 6 };
static const ber_tlv_tag_t asn_DEF_HeaderInfo_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_HeaderInfo_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* itsAid */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* hashAlg */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* genTime */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* expiryTime */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* location */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* digest */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* encKey */
};
asn_SEQUENCE_specifics_t asn_SPC_HeaderInfo_specs_1 = {
	sizeof(struct HeaderInfo),
	offsetof(struct HeaderInfo, _asn_ctx),
	asn_MAP_HeaderInfo_tag2el_1,
	7,	/* Count of tags in the map */
	asn_MAP_HeaderInfo_oms_1,	/* Optional members */
	6, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_HeaderInfo = {
	"HeaderInfo",
	"HeaderInfo",
	&asn_OP_SEQUENCE,
	asn_DEF_HeaderInfo_tags_1,
	sizeof(asn_DEF_HeaderInfo_tags_1)
		/sizeof(asn_DEF_HeaderInfo_tags_1[0]), /* 1 */
	asn_DEF_HeaderInfo_tags_1,	/* Same as above */
	sizeof(asn_DEF_HeaderInfo_tags_1)
		/sizeof(asn_DEF_HeaderInfo_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_HeaderInfo_1,
	7,	/* Elements count */
	&asn_SPC_HeaderInfo_specs_1	/* Additional specs */
};


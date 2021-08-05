/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "PublicEncryptionKey.h"

asn_TYPE_member_t asn_MBR_PublicEncryptionKey_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PublicEncryptionKey, supportedSymmAlg),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SymmetricAlgorithm,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"supportedSymmAlg"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PublicEncryptionKey, eccCurve),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_EccCurve,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"eccCurve"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PublicEncryptionKey, publicKey),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_ECCPoint,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"publicKey"
		},
};
static const ber_tlv_tag_t asn_DEF_PublicEncryptionKey_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PublicEncryptionKey_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* supportedSymmAlg */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* eccCurve */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* publicKey */
};
asn_SEQUENCE_specifics_t asn_SPC_PublicEncryptionKey_specs_1 = {
	sizeof(struct PublicEncryptionKey),
	offsetof(struct PublicEncryptionKey, _asn_ctx),
	asn_MAP_PublicEncryptionKey_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_PublicEncryptionKey = {
	"PublicEncryptionKey",
	"PublicEncryptionKey",
	&asn_OP_SEQUENCE,
	asn_DEF_PublicEncryptionKey_tags_1,
	sizeof(asn_DEF_PublicEncryptionKey_tags_1)
		/sizeof(asn_DEF_PublicEncryptionKey_tags_1[0]), /* 1 */
	asn_DEF_PublicEncryptionKey_tags_1,	/* Same as above */
	sizeof(asn_DEF_PublicEncryptionKey_tags_1)
		/sizeof(asn_DEF_PublicEncryptionKey_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_PublicEncryptionKey_1,
	3,	/* Elements count */
	&asn_SPC_PublicEncryptionKey_specs_1	/* Additional specs */
};

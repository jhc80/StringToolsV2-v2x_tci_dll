/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciSecMsgFrame"
 * 	found in "asn/sec_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SecurityResultCode.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_SecurityResultCode_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_SecurityResultCode_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  4,  4,  0,  15 }	/* (0..15,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_SecurityResultCode_value2enum_1[] = {
	{ 0,	7,	"unknown" },
	{ 1,	29,	"incorrectSecureMessageVersion" },
	{ 2,	19,	"incorrectSignerType" },
	{ 3,	20,	"incorrectCertVersion" },
	{ 4,	24,	"incorrectCertIssueDigest" },
	{ 5,	24,	"incorrectCertSubjectInfo" },
	{ 6,	29,	"incorrectCertSubjectAttribute" },
	{ 7,	27,	"incorrectCertValidityPeriod" },
	{ 8,	28,	"incorrectCertTimeStartAndEnd" },
	{ 9,	25,	"incorrectSubcertAuthority" },
	{ 10,	18,	"incorrectCertChain" },
	{ 11,	22,	"incorrectCertSignature" },
	{ 12,	23,	"incorrectTbsDataGenTime" },
	{ 13,	23,	"incorrectTbsDataHashAlg" },
	{ 14,	22,	"incorrectTbsDataItsAid" },
	{ 15,	31,	"incorrectSignedMessageSignature" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_SecurityResultCode_enum2value_1[] = {
	10,	/* incorrectCertChain(10) */
	4,	/* incorrectCertIssueDigest(4) */
	11,	/* incorrectCertSignature(11) */
	6,	/* incorrectCertSubjectAttribute(6) */
	5,	/* incorrectCertSubjectInfo(5) */
	8,	/* incorrectCertTimeStartAndEnd(8) */
	7,	/* incorrectCertValidityPeriod(7) */
	3,	/* incorrectCertVersion(3) */
	1,	/* incorrectSecureMessageVersion(1) */
	15,	/* incorrectSignedMessageSignature(15) */
	2,	/* incorrectSignerType(2) */
	9,	/* incorrectSubcertAuthority(9) */
	12,	/* incorrectTbsDataGenTime(12) */
	13,	/* incorrectTbsDataHashAlg(13) */
	14,	/* incorrectTbsDataItsAid(14) */
	0	/* unknown(0) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_SecurityResultCode_specs_1 = {
	asn_MAP_SecurityResultCode_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_SecurityResultCode_enum2value_1,	/* N => "tag"; sorted by N */
	16,	/* Number of elements in the maps */
	17,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_SecurityResultCode_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_SecurityResultCode = {
	"SecurityResultCode",
	"SecurityResultCode",
	&asn_OP_NativeEnumerated,
	asn_DEF_SecurityResultCode_tags_1,
	sizeof(asn_DEF_SecurityResultCode_tags_1)
		/sizeof(asn_DEF_SecurityResultCode_tags_1[0]), /* 1 */
	asn_DEF_SecurityResultCode_tags_1,	/* Same as above */
	sizeof(asn_DEF_SecurityResultCode_tags_1)
		/sizeof(asn_DEF_SecurityResultCode_tags_1[0]), /* 1 */
	{ &asn_OER_type_SecurityResultCode_constr_1, &asn_PER_type_SecurityResultCode_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_SecurityResultCode_specs_1	/* Additional specs */
};

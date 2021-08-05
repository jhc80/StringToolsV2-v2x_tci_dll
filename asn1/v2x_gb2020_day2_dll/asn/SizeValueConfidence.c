/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SensorSharing"
 * 	found in "asn/SensorSharing.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SizeValueConfidence.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_SizeValueConfidence_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_SizeValueConfidence_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  13 }	/* (0..13) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_SizeValueConfidence_value2enum_1[] = {
	{ 0,	11,	"unavailable" },
	{ 1,	11,	"size-100-00" },
	{ 2,	11,	"size-050-00" },
	{ 3,	11,	"size-020-00" },
	{ 4,	11,	"size-010-00" },
	{ 5,	11,	"size-005-00" },
	{ 6,	11,	"size-002-00" },
	{ 7,	11,	"size-001-00" },
	{ 8,	11,	"size-000-50" },
	{ 9,	11,	"size-000-20" },
	{ 10,	11,	"size-000-10" },
	{ 11,	11,	"size-000-05" },
	{ 12,	11,	"size-000-02" },
	{ 13,	11,	"size-000-01" }
};
static const unsigned int asn_MAP_SizeValueConfidence_enum2value_1[] = {
	13,	/* size-000-01(13) */
	12,	/* size-000-02(12) */
	11,	/* size-000-05(11) */
	10,	/* size-000-10(10) */
	9,	/* size-000-20(9) */
	8,	/* size-000-50(8) */
	7,	/* size-001-00(7) */
	6,	/* size-002-00(6) */
	5,	/* size-005-00(5) */
	4,	/* size-010-00(4) */
	3,	/* size-020-00(3) */
	2,	/* size-050-00(2) */
	1,	/* size-100-00(1) */
	0	/* unavailable(0) */
};
const asn_INTEGER_specifics_t asn_SPC_SizeValueConfidence_specs_1 = {
	asn_MAP_SizeValueConfidence_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_SizeValueConfidence_enum2value_1,	/* N => "tag"; sorted by N */
	14,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_SizeValueConfidence_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_SizeValueConfidence = {
	"SizeValueConfidence",
	"SizeValueConfidence",
	&asn_OP_NativeEnumerated,
	asn_DEF_SizeValueConfidence_tags_1,
	sizeof(asn_DEF_SizeValueConfidence_tags_1)
		/sizeof(asn_DEF_SizeValueConfidence_tags_1[0]), /* 1 */
	asn_DEF_SizeValueConfidence_tags_1,	/* Same as above */
	sizeof(asn_DEF_SizeValueConfidence_tags_1)
		/sizeof(asn_DEF_SizeValueConfidence_tags_1[0]), /* 1 */
	{ &asn_OER_type_SizeValueConfidence_constr_1, &asn_PER_type_SizeValueConfidence_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_SizeValueConfidence_specs_1	/* Additional specs */
};

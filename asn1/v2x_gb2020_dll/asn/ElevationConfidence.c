/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DefPosition"
 * 	found in "asn/DefPosition.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "ElevationConfidence.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_ElevationConfidence_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_ElevationConfidence_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_ElevationConfidence_value2enum_1[] = {
	{ 0,	11,	"unavailable" },
	{ 1,	11,	"elev-500-00" },
	{ 2,	11,	"elev-200-00" },
	{ 3,	11,	"elev-100-00" },
	{ 4,	11,	"elev-050-00" },
	{ 5,	11,	"elev-020-00" },
	{ 6,	11,	"elev-010-00" },
	{ 7,	11,	"elev-005-00" },
	{ 8,	11,	"elev-002-00" },
	{ 9,	11,	"elev-001-00" },
	{ 10,	11,	"elev-000-50" },
	{ 11,	11,	"elev-000-20" },
	{ 12,	11,	"elev-000-10" },
	{ 13,	11,	"elev-000-05" },
	{ 14,	11,	"elev-000-02" },
	{ 15,	11,	"elev-000-01" }
};
static const unsigned int asn_MAP_ElevationConfidence_enum2value_1[] = {
	15,	/* elev-000-01(15) */
	14,	/* elev-000-02(14) */
	13,	/* elev-000-05(13) */
	12,	/* elev-000-10(12) */
	11,	/* elev-000-20(11) */
	10,	/* elev-000-50(10) */
	9,	/* elev-001-00(9) */
	8,	/* elev-002-00(8) */
	7,	/* elev-005-00(7) */
	6,	/* elev-010-00(6) */
	5,	/* elev-020-00(5) */
	4,	/* elev-050-00(4) */
	3,	/* elev-100-00(3) */
	2,	/* elev-200-00(2) */
	1,	/* elev-500-00(1) */
	0	/* unavailable(0) */
};
const asn_INTEGER_specifics_t asn_SPC_ElevationConfidence_specs_1 = {
	asn_MAP_ElevationConfidence_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_ElevationConfidence_enum2value_1,	/* N => "tag"; sorted by N */
	16,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_ElevationConfidence_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_ElevationConfidence = {
	"ElevationConfidence",
	"ElevationConfidence",
	&asn_OP_NativeEnumerated,
	asn_DEF_ElevationConfidence_tags_1,
	sizeof(asn_DEF_ElevationConfidence_tags_1)
		/sizeof(asn_DEF_ElevationConfidence_tags_1[0]), /* 1 */
	asn_DEF_ElevationConfidence_tags_1,	/* Same as above */
	sizeof(asn_DEF_ElevationConfidence_tags_1)
		/sizeof(asn_DEF_ElevationConfidence_tags_1[0]), /* 1 */
	{ &asn_OER_type_ElevationConfidence_constr_1, &asn_PER_type_ElevationConfidence_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_ElevationConfidence_specs_1	/* Additional specs */
};


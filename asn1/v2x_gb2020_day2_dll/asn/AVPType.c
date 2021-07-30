/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "PAM"
 * 	found in "asn/PAM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "AVPType.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_AVPType_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_AVPType_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  5 }	/* (0..5,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_AVPType_value2enum_1[] = {
	{ 0,	2,	"p0" },
	{ 1,	2,	"p1" },
	{ 2,	2,	"p2" },
	{ 3,	2,	"p3" },
	{ 4,	2,	"p4" },
	{ 5,	2,	"p5" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_AVPType_enum2value_1[] = {
	0,	/* p0(0) */
	1,	/* p1(1) */
	2,	/* p2(2) */
	3,	/* p3(3) */
	4,	/* p4(4) */
	5	/* p5(5) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_AVPType_specs_1 = {
	asn_MAP_AVPType_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_AVPType_enum2value_1,	/* N => "tag"; sorted by N */
	6,	/* Number of elements in the maps */
	7,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_AVPType_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_AVPType = {
	"AVPType",
	"AVPType",
	&asn_OP_NativeEnumerated,
	asn_DEF_AVPType_tags_1,
	sizeof(asn_DEF_AVPType_tags_1)
		/sizeof(asn_DEF_AVPType_tags_1[0]), /* 1 */
	asn_DEF_AVPType_tags_1,	/* Same as above */
	sizeof(asn_DEF_AVPType_tags_1)
		/sizeof(asn_DEF_AVPType_tags_1[0]), /* 1 */
	{ &asn_OER_type_AVPType_constr_1, &asn_PER_type_AVPType_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_AVPType_specs_1	/* Additional specs */
};


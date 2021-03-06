/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "OBU"
 * 	found in "asn/OBU.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "VehicleType.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_VehicleType_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_VehicleType_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  3,  3,  0,  4 }	/* (0..4,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_VehicleType_value2enum_1[] = {
	{ 0,	7,	"unknown" },
	{ 1,	9,	"pedstrain" },
	{ 2,	7,	"bicycle" },
	{ 3,	10,	"motorcycle" },
	{ 4,	3,	"car" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_VehicleType_enum2value_1[] = {
	2,	/* bicycle(2) */
	4,	/* car(4) */
	3,	/* motorcycle(3) */
	1,	/* pedstrain(1) */
	0	/* unknown(0) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_VehicleType_specs_1 = {
	asn_MAP_VehicleType_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_VehicleType_enum2value_1,	/* N => "tag"; sorted by N */
	5,	/* Number of elements in the maps */
	6,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_VehicleType_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_VehicleType = {
	"VehicleType",
	"VehicleType",
	&asn_OP_NativeEnumerated,
	asn_DEF_VehicleType_tags_1,
	sizeof(asn_DEF_VehicleType_tags_1)
		/sizeof(asn_DEF_VehicleType_tags_1[0]), /* 1 */
	asn_DEF_VehicleType_tags_1,	/* Same as above */
	sizeof(asn_DEF_VehicleType_tags_1)
		/sizeof(asn_DEF_VehicleType_tags_1[0]), /* 1 */
	{ &asn_OER_type_VehicleType_constr_1, &asn_PER_type_VehicleType_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_VehicleType_specs_1	/* Additional specs */
};


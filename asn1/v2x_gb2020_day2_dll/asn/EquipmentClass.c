/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "EquipmentClass.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_EquipmentClass_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_EquipmentClass_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  2,  2,  0,  2 }	/* (0..2,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_EquipmentClass_value2enum_1[] = {
	{ 0,	10,	"onechipOBU" },
	{ 1,	6,	"iccOBU" },
	{ 2,	6,	"cpcOBU" }
	/* This list is extensible */
};
static const unsigned int asn_MAP_EquipmentClass_enum2value_1[] = {
	2,	/* cpcOBU(2) */
	1,	/* iccOBU(1) */
	0	/* onechipOBU(0) */
	/* This list is extensible */
};
const asn_INTEGER_specifics_t asn_SPC_EquipmentClass_specs_1 = {
	asn_MAP_EquipmentClass_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_EquipmentClass_enum2value_1,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	4,	/* Extensions before this member */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_EquipmentClass_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_EquipmentClass = {
	"EquipmentClass",
	"EquipmentClass",
	&asn_OP_NativeEnumerated,
	asn_DEF_EquipmentClass_tags_1,
	sizeof(asn_DEF_EquipmentClass_tags_1)
		/sizeof(asn_DEF_EquipmentClass_tags_1[0]), /* 1 */
	asn_DEF_EquipmentClass_tags_1,	/* Same as above */
	sizeof(asn_DEF_EquipmentClass_tags_1)
		/sizeof(asn_DEF_EquipmentClass_tags_1[0]), /* 1 */
	{ &asn_OER_type_EquipmentClass_constr_1, &asn_PER_type_EquipmentClass_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_EquipmentClass_specs_1	/* Additional specs */
};


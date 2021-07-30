/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "TciMsgLayerFrame"
 * 	found in "asn/msg_conformance.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "MsgType.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_MsgType_constr_1 CC_NOTUSED = {
	{ 0, 0 },
	-1};
asn_per_constraints_t asn_PER_type_MsgType_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  6 }	/* (0..6) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_MsgType_value2enum_1[] = {
	{ 0,	10,	"bsmMsgType" },
	{ 1,	14,	"mapRelativePos" },
	{ 2,	14,	"mapAbsolutePos" },
	{ 3,	16,	"spatTimeCounting" },
	{ 4,	13,	"spatUTCTiming" },
	{ 5,	10,	"rsiMsgType" },
	{ 6,	10,	"rsmMsgType" }
};
static const unsigned int asn_MAP_MsgType_enum2value_1[] = {
	0,	/* bsmMsgType(0) */
	2,	/* mapAbsolutePos(2) */
	1,	/* mapRelativePos(1) */
	5,	/* rsiMsgType(5) */
	6,	/* rsmMsgType(6) */
	3,	/* spatTimeCounting(3) */
	4	/* spatUTCTiming(4) */
};
const asn_INTEGER_specifics_t asn_SPC_MsgType_specs_1 = {
	asn_MAP_MsgType_value2enum_1,	/* "tag" => N; sorted by tag */
	asn_MAP_MsgType_enum2value_1,	/* N => "tag"; sorted by N */
	7,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_MsgType_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
asn_TYPE_descriptor_t asn_DEF_MsgType = {
	"MsgType",
	"MsgType",
	&asn_OP_NativeEnumerated,
	asn_DEF_MsgType_tags_1,
	sizeof(asn_DEF_MsgType_tags_1)
		/sizeof(asn_DEF_MsgType_tags_1[0]), /* 1 */
	asn_DEF_MsgType_tags_1,	/* Same as above */
	sizeof(asn_DEF_MsgType_tags_1)
		/sizeof(asn_DEF_MsgType_tags_1[0]), /* 1 */
	{ &asn_OER_type_MsgType_constr_1, &asn_PER_type_MsgType_constr_1, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_MsgType_specs_1	/* Additional specs */
};


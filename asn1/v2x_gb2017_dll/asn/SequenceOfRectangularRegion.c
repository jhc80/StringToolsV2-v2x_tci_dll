/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#include "SequenceOfRectangularRegion.h"

asn_TYPE_member_t asn_MBR_SequenceOfRectangularRegion_1[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_RectangularRegion,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_SequenceOfRectangularRegion_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
asn_SET_OF_specifics_t asn_SPC_SequenceOfRectangularRegion_specs_1 = {
	sizeof(struct SequenceOfRectangularRegion),
	offsetof(struct SequenceOfRectangularRegion, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
asn_TYPE_descriptor_t asn_DEF_SequenceOfRectangularRegion = {
	"SequenceOfRectangularRegion",
	"SequenceOfRectangularRegion",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_SequenceOfRectangularRegion_tags_1,
	sizeof(asn_DEF_SequenceOfRectangularRegion_tags_1)
		/sizeof(asn_DEF_SequenceOfRectangularRegion_tags_1[0]), /* 1 */
	asn_DEF_SequenceOfRectangularRegion_tags_1,	/* Same as above */
	sizeof(asn_DEF_SequenceOfRectangularRegion_tags_1)
		/sizeof(asn_DEF_SequenceOfRectangularRegion_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_SequenceOfRectangularRegion_1,
	1,	/* Single element */
	&asn_SPC_SequenceOfRectangularRegion_specs_1	/* Additional specs */
};


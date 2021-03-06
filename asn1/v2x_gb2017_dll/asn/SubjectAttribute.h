/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ieee1GMV2X"
 * 	found in "asn/GM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SubjectAttribute_H_
#define	_SubjectAttribute_H_


#include <asn_application.h>

/* Including external dependencies */
#include "PublicVerifyKey.h"
#include "SubjectAssurance.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct PublicEncryptionKey;
struct SequenceOfitsAidList;
struct SequenceOfitsAidSspList;

/* SubjectAttribute */
typedef struct SubjectAttribute {
	PublicVerifyKey_t	 verificationKey;
	struct PublicEncryptionKey	*encryptionKey	/* OPTIONAL */;
	SubjectAssurance_t	*assuranceLevel	/* OPTIONAL */;
	struct SequenceOfitsAidList	*itsAidList	/* OPTIONAL */;
	struct SequenceOfitsAidSspList	*itsAidSspList	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SubjectAttribute_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SubjectAttribute;
extern asn_SEQUENCE_specifics_t asn_SPC_SubjectAttribute_specs_1;
extern asn_TYPE_member_t asn_MBR_SubjectAttribute_1[5];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "PublicEncryptionKey.h"
#include "SequenceOfitsAidList.h"
#include "SequenceOfitsAidSspList.h"

#endif	/* _SubjectAttribute_H_ */
#include <asn_internal.h>

/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "VPM"
 * 	found in "asn/VPM.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_SetTollDataRq_H_
#define	_SetTollDataRq_H_


#include <asn_application.h>

/* Including external dependencies */
#include "RandStr8.h"
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct TransPara;
struct PartOfFile;
struct TollingPos;

/* SetTollDataRq */
typedef struct SetTollDataRq {
	RandStr8_t	*rndRSU	/* OPTIONAL */;
	struct TransPara	*transPara	/* OPTIONAL */;
	struct PartOfFile	*tollInfo	/* OPTIONAL */;
	struct TollingPos	*tollingPos	/* OPTIONAL */;
	long	*keyIdForAuthen	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SetTollDataRq_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SetTollDataRq;
extern asn_SEQUENCE_specifics_t asn_SPC_SetTollDataRq_specs_1;
extern asn_TYPE_member_t asn_MBR_SetTollDataRq_1[5];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "TransPara.h"
#include "PartOfFile.h"
#include "TollingPos.h"

#endif	/* _SetTollDataRq_H_ */
#include <asn_internal.h>

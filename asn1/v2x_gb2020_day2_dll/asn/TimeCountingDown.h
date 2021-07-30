/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SignalPhaseAndTiming"
 * 	found in "asn/SignalPhaseAndTiming.asn"
 * 	`asn1c -fcompound-names -fnative-types -Werror -gen-PER -pdu=all`
 */

#ifndef	_TimeCountingDown_H_
#define	_TimeCountingDown_H_


#include <asn_application.h>

/* Including external dependencies */
#include "TimeMark.h"
#include "Confidence.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* TimeCountingDown */
typedef struct TimeCountingDown {
	TimeMark_t	 startTime;
	TimeMark_t	*minEndTime	/* OPTIONAL */;
	TimeMark_t	*maxEndTime	/* OPTIONAL */;
	TimeMark_t	 likelyEndTime;
	Confidence_t	*timeConfidence	/* OPTIONAL */;
	TimeMark_t	*nextStartTime	/* OPTIONAL */;
	TimeMark_t	*nextDuration	/* OPTIONAL */;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} TimeCountingDown_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_TimeCountingDown;
extern asn_SEQUENCE_specifics_t asn_SPC_TimeCountingDown_specs_1;
extern asn_TYPE_member_t asn_MBR_TimeCountingDown_1[7];

#ifdef __cplusplus
}
#endif

#endif	/* _TimeCountingDown_H_ */
#include <asn_internal.h>

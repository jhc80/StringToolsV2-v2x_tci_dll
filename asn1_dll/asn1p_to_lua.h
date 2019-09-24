#ifndef __ASN1P_TO_LUA_H
#define __ASN1P_TO_LUA_H

#include "cruntime.h"

char* asn1_parse_all_files(const char *filelist[], int list_size, int *ret_len);
char* asn1_parse_string(const void *buf,int buf_size, int *ret_len);

#endif


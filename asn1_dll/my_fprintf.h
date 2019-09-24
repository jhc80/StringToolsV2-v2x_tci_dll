#ifndef __MY_FPRINTF_H
#define __MY_FPRINTF_H

#include "syslog.h"

#define my_fprintf(fp,...) do{\
    syslog_printf(__VA_ARGS__);\
}while(0)\

#define my_printf(...) do{\
    syslog_printf(__VA_ARGS__);\
}while(0)\

#endif
#ifndef __CONFIG_H
#define __CONFIG_H

#define _LINUX_ 	0
#define _WIN32_		1
#define _WM6X_		0
#define _WIN64_		0
#define _MAC64_		0
#define _IOS32_		0
#define _GBAVM_		0
#define _WINCE_		0
#define _ANDROID_	0

#define _ASC_       1
#define _UNICODE_   1
#define _DEBUG_     1

#ifdef __x86_64__
#define _LINUX64_   1
#undef _LINUX_
#endif

#if _LINUX_ || _LINUX64_
#define _IS_LINUX_ 1
#endif

#if _WIN32_ || _WIN64_ 
#define _IS_WINDOWS_ 1
#endif

#if _WIN32_
#define SYSLOG_ADVANCE  0
#else
#define SYSLOG_ADVANCE  1
#endif

#endif


/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of Uplink Laboratories.
 *
 *   (c) 2006-2007 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_cc_datatypes_h
#define __included_cc_datatypes_h

typedef char cc_int8_t;
typedef unsigned char cc_uint8_t;
typedef short cc_int16_t;
typedef unsigned short cc_uint16_t;
typedef int cc_int32_t;
typedef unsigned int cc_uint32_t;
#ifndef TARGET_OS_WINDOWS
typedef long long cc_int64_t;
typedef unsigned long long cc_uint64_t;
#else
typedef __int64 cc_int64_t;
typedef unsigned __int64 cc_uint64_t;
#endif

#ifdef TARGET_OS_WINDOWS
typedef cc_int64_t fpos64_t;
#endif

#endif

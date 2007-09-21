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

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#ifndef TARGET_OS_WINDOWS
typedef long long int64_t;
typedef unsigned long long uint64_t;
#else
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif

#endif
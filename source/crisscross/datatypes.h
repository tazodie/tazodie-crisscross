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

typedef long cc_long_t;
typedef unsigned long cc_ulong_t;

typedef long long cc_int64_t;
typedef unsigned long long cc_uint64_t;

#ifdef TARGET_OS_WINDOWS
typedef cc_int64_t fpos64_t;
#elif defined ( TARGET_OS_MACOSX )
typedef fpos64_t fpos_t;
#endif

typedef float cc_float32_t;
typedef double cc_float64_t;

typedef void * cc_ptr_t;

typedef bool cc_bool_t;

#endif

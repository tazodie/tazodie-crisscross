/*
 *   CrissCross
 *   A multi-purpose cross-platform library.
 *
 *   A product of IO.IN Research.
 *
 *   (c) 2006-2008 Steven Noonan.
 *   Licensed under the New BSD License.
 *
 */

#ifndef __included_header_h
#define __included_header_h

#include <math.h>
#include <time.h>

#include <crisscross/crisscross.h>

#define DATASET_SIZE    100
#define ENTRY_LENGTH    1024
#ifdef TARGET_OS_NDSFIRMWARE
#  define MAX_RUNS        10
#else
#  define MAX_RUNS        500
#endif

#endif

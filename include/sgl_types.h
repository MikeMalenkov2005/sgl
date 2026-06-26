#ifndef SGL_TYPES_H
#define SGL_TYPES_H

#include <float.h>
#include <limits.h>
#include <stddef.h>

typedef signed char schar;
typedef unsigned char uchar;

typedef signed short shrt;
typedef unsigned short ushort, ushrt;

typedef unsigned int uint;
typedef unsigned long ulong;

typedef signed long long llong;
typedef unsigned long long ullong;

#define USHORT_MAX  USHRT_MAX
#define SHORT_MAX   SHRT_MAX
#define SHORT_MIN   SHRT_MIN

#if !defined(__STDC_VERSION) || __STDC_VERSION < 199901L
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#define true  1
#define false 0
typedef uchar bool;
#endif
#else
#include <stdbool.h>
#endif

typedef bool boolean;

#endif


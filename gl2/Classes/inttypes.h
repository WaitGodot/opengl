//
// Created by mvp@mvplayer.net
// FIXME: use official inttypes.h
//
#include "stdint.h"

#if _MSC_VER
#define snprintf _snprintf
#endif

#ifndef INT64_C
#define INT64_C
#define UINT64_C
#endif

#define INT64_C(val) val##i64
#define _64BITARG_ "I64"
#define PRId64     _64BITARG_"d"
#define PRIu64     _64BITARG_"u"
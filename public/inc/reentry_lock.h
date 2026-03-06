#ifndef _REENTRY_LOCK_H_
#define _REENTRY_LOCK_H_

#if __has_include("config.h")
#include "config.h"
#endif

#ifndef NEWLIB_HEAP_SIZE
#define NEWLIB_HEAP_SIZE        (16 * 1024)
#endif 

size_t newlib_heap_max();

#endif
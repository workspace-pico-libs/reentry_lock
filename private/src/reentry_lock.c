#include <errno.h>
#include <stddef.h>
#include "config.h"
#include "reentry_lock.h"
#include "reentry_lock_priv.h"

#include "FreeRTOS.h"
#include "semphr.h"

static uint8_t newlib_heap[NEWLIB_HEAP_SIZE];
static uint8_t *heap_ptr = newlib_heap;

static size_t newlib_heap_max_var;

static SemaphoreHandle_t malloc_lock = NULL;

void *_sbrk(ptrdiff_t incr)
{
    uint8_t *prev = heap_ptr;
    uint8_t *next = heap_ptr + incr;

    if (next > newlib_heap + NEWLIB_HEAP_SIZE) {
        errno = ENOMEM;
        return (void *)-1;
    }

    heap_ptr = next;

    size_t used = heap_ptr - newlib_heap;
    if (used > newlib_heap_max_var)
        newlib_heap_max_var = used;

    return prev;
}

void __malloc_lock(struct _reent *r)
{
    (void)r;

    // fully transparent – tak jak wcześniej
    if (malloc_lock == NULL)
    {
        malloc_lock = xSemaphoreCreateMutex();
        configASSERT(malloc_lock);
    }

    xSemaphoreTake(malloc_lock, portMAX_DELAY);
}

void __malloc_unlock(struct _reent *r)
{
    (void)r;
    xSemaphoreGive(malloc_lock);
}

size_t newlib_heap_max()
{
    return newlib_heap_max_var;
}

size_t newlib_heap_size()
{
    static size_t newlib_heap_size_var=NEWLIB_HEAP_SIZE;
    return newlib_heap_size_var;
}
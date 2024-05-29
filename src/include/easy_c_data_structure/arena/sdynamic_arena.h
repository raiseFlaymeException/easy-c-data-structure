#ifndef SDYNAMIC_ARENA_H
#define SDYNAMIC_ARENA_H

#include "../array/carray_creator.h"

CARRAY_CREATE_DECLARATION(SDynamicArena, unsigned char);

void *SDynamicArena_get_bytes(SDynamicArena *arena, size_t size); // NOLINT

#endif                                                            // DYNAMIC_ARENA_H

// #ifdef SDYNAMiC_ARENA_IMPL
CARRAY_CREATE_DEFINITION(SDynamicArena, unsigned char);

void *SDynamicArena_get_bytes(SDynamicArena *arena, size_t size) {
    if (arena->cap <= arena->size + size) { SDynamicArena_extend(arena, arena->cap * 2); }

    size_t ptr_idx = arena->size;
    arena->size += size;

    return arena->data + ptr_idx;
}

// #endif // SDYNAMiC_ARENA_IMPL

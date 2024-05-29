#include <stdbool.h>

#include <stdio.h>

#define USE_STATIC_ARENA 0

#define ARENA_SIZE 1024

#if USE_STATIC_ARENA
#include "easy_c_data_structure/arena/cstatic_arena_creator.h"
CSTATIC_ARENA_DECLARATION(StaticArena, ARENA_SIZE)
CSTATIC_ARENA_DEFINITION(StaticArena, ARENA_SIZE)
#else
#define SDYNAMIC_ARENA_IMPL
#include "easy_c_data_structure/arena/sdynamic_arena.h"
#endif

int main() {
#if USE_STATIC_ARENA
    StaticArena arena;
    StaticArena_init(&arena, true);
#else
    SDynamicArena arena;
    SDynamicArena_alloc(&arena, ARENA_SIZE);
#endif

    size_t size;

    printf("Enter a size: ");
    scanf("%d", &size);

#if USE_STATIC_ARENA
    char *data = (char *)StaticArena_get_bytes(&arena, sizeof(char) * size);
#else
    char *data = (char *)SDynamicArena_get_bytes(&arena, sizeof(char) * size);
#endif

    printf("Enter your name (max %d characters): ", size);
    scanf("%s", data); // (it's an example I know it's unsafe)
    printf("your name is: %s\n", data);

#if !USE_STATIC_ARENA
    SDynamicArena_free(&arena);
#endif
    return 0;
}

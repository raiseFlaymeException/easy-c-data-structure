#ifndef CSTATIC_ARENA_ALLOCATOR
#define CSTATIC_ARENA_ALLOCATOR

#define CSTATIC_ARENA_DECLARATION_STRUCT(name, max_size) \
    typedef struct { \
        unsigned char bytes[max_size]; \
        size_t        size; \
    } StaticArena; 

#define CSTATIC_ARENA_DECLARATION_FUNCTION(name) \
    void name##_init(name *arena, bool zero); \
    void *name##_get_bytes(name *arena, size_t size);

#define CSTATIC_ARENA_DECLARATION(name, max_size) \
    CSTATIC_ARENA_DECLARATION_STRUCT(name, max_size) \
    CSTATIC_ARENA_DECLARATION_FUNCTION(name) \

#define CSTATIC_ARENA_DEFINITION(name, max_size) \
    void name##_init(name *arena, bool zero) { \
        arena->size = 0; \
        \
        if (zero) { \
            for (size_t i = 0; i < max_size; i++) { arena->bytes[i] = 0; } \
        } \
    } \
    void *name##_get_bytes(name *arena, size_t size) { \
        size_t ptr_idx = arena->size; \
        arena->size += size; \
        \
        return arena->bytes + ptr_idx; \
    }

#endif // CSTATIC_ARENA_ALLOCATOR

#ifndef CHASHMAP_CREATOR_H
#define CHASHMAP_CREATOR_H

#include <stdbool.h>

#include "array/carray_creator.h"

// struct name##_pair { \
//     key_type key; \
//     value_type value; \
//     bool taken; \
// }; 
#define CHASHMAP_DECLARATION_STRUCT(name, key_type, value_type) \
    struct name { \
        CARRAY_CREATE_DECLARATION_STRUCT_NOTDSC(name##_pair_array, \
            struct name##_pair { \
                key_type key; \
                value_type value; \
                bool taken; \
            } \
        ) cells; \
    }; \
    typedef struct name##_pair_array name##_pair_array; \
    typedef struct name name;

#define CHASHMAP_DECLARATION_FUNCTION(name, key_type, value_type) \
    CARRAY_CREATE_DECLARATION_FUNCTION(name##_pair_array, struct name##_pair) \
    size_t _##name##_get_idx(struct name *hashmap, key_type key); \
    void name##_alloc(struct name *hashmap, size_t cap); \
    void name##_free(struct name *hashmap); \
    void name##_insert(struct name *hashmap, key_type key, value_type value); \
    value_type name##_get(struct name *hashmap, key_type key);

#define CHASHMAP_DECLARATION(name, key_type, value_type) \
    CHASHMAP_DECLARATION_STRUCT(name, key_type, value_type) \
    CHASHMAP_DECLARATION_FUNCTION(name, key_type, value_type)

#define CHASHMAP_DEFINITION(name, key_type, value_type, hash_func) \
    CARRAY_CREATE_DEFINITION(name##_pair_array, struct name##_pair)
    // void name##_alloc(struct name *hashmap, size_t cap); \
    // void name##_free(struct name *hashmap); \
    // void name##_insert(struct name *hashmap, key_type key, value_type value); \
    // value_type name##_get(struct name *hashmap, key_type key);


#endif // CHASHMAP_CREATOR_H

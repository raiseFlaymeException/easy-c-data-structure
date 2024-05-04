#ifndef CHASHMAP_CREATOR_H
#define CHASHMAP_CREATOR_H

#include <stdlib.h>
#include <stdbool.h>
#include "array/carray_creator.h"

#define CHASHMAP_CREATE_DECLARATION_STRUCT(name, key_type, value_type) \
    typedef struct { \
        key_type key; \
        value_type value; \
        bool taken; \
        bool removed; \
    } name##_cell; \
    CARRAY_CREATE_DECLARATION(name##_cells, name##_cell) \
    typedef struct name##_cells name;

#define CHASHMAP_CREATE_DECLARATION_FUNCTION(name, key_type, value_type) \
    void name##_alloc(name *hashmap, size_t cap); \
    void name##_free(name *hashmap); \
    bool name##_insert(name *hashmap, key_type key, value_type value); \
    bool name##_get(name *hashmap, key_type key, value_type *value); \
    bool name##_remove(name *hashmap, key_type key);

#define CHASHMAP_CREATE_DECLARATION(name, key_type, value_type) \
    CHASHMAP_CREATE_DECLARATION_STRUCT(name, key_type, value_type) \
    CHASHMAP_CREATE_DECLARATION_FUNCTION(name, key_type, value_type)

#define CHASHMAP_CREATE_DEFINITION(name, key_type, value_type, hash) \
    CARRAY_CREATE_DEFINITION(name##_cells, name##_cell) \
    void name##_alloc(name *hashmap, size_t cap) { \
        name##_cells_alloc(hashmap, cap); \
        for (size_t i=0; i<cap; i++) { \
            hashmap->data[i].taken = false; \
            hashmap->data[i].removed = false; \
        } \
    } \
    void name##_free(name *hashmap) { \
        name##_cells_free(hashmap); \
    } \
    bool name##_insert(name *hashmap, key_type key, value_type value) { \
        bool result=true; \
        \
        if (hashmap->size>=hashmap->cap) { \
            name old_hashmap = *hashmap; \
            \
            name##_cells_alloc(hashmap, hashmap->cap*2+1); \
            \
            for (size_t i=0; i<hashmap->cap; i++) { \
                hashmap->data[i].taken = false; \
                hashmap->data[i].removed = false; \
            } \
            \
            for (size_t i=0; i<old_hashmap.cap; i++) { \
                if (!old_hashmap.data[i].taken || old_hashmap.data[i].removed) { \
                    continue; \
                } \
                if (!name##_insert(hashmap, old_hashmap.data[i].key, old_hashmap.data[i].value)) { \
                    result = false; \
                } \
            } \
            \
            name##_free(&old_hashmap); \
        } \
        hashmap->size++; \
        \
        size_t idx = hash(key) % hashmap->cap; \
        \
        while (hashmap->data[idx].taken && !hashmap->data[idx].removed) { \
            if (hashmap->data[idx].key==key) { \
                return false; \
            } \
            idx = (idx + 1) % hashmap->cap; \
        } \
        \
        hashmap->data[idx].key = key; \
        hashmap->data[idx].value = value; \
        hashmap->data[idx].taken = true; \
        \
        return result; \
    } \
    bool name##_get(name *hashmap, key_type key, value_type *value) { \
        size_t idx = hash(key) % hashmap->cap; \
        \
        for (size_t i=0; i<hashmap->cap; i++) { \
            if (hashmap->data[idx].taken && hashmap->data[idx].key==key && !hashmap->data[idx].removed) { \
                *value = hashmap->data[idx].value; \
                return true; \
            } \
            idx = (idx + 1) % hashmap->cap; \
        } \
        return false; \
    } \
    bool name##_remove(name *hashmap, size_t key) { \
        size_t idx = hash(key) % hashmap->cap; \
        \
        for (size_t i=0; i<hashmap->cap; i++) { \
            if (hashmap->data[idx].taken && hashmap->data[idx].key==key && !hashmap->data[idx].removed) { \
                hashmap->data[idx].removed = true; \
                hashmap->size++; \
                \
                return true; \
            } \
            idx = (idx + 1) % hashmap->cap; \
        } \
        return false; \
    }

#endif // CHASHMAP_CREATOR_H

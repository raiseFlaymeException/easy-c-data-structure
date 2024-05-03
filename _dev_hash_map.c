#include <stdio.h>

#include "_dev_hash_map/chashmap_creator.h"

size_t hash(size_t key) {
    return key;
}

CHASHMAP_DECLARATION(ULLStringHashMap, size_t, const char *)
CHASHMAP_DEFINITION(ULLStringHashMap, size_t, const char *, hash)

size_t _ULLStringHashMap_get_index(struct ULLStringHashMap *hashmap, size_t key) {
    size_t idx = hash(key);

    while (hashmap->cells.data[idx].taken) {
        idx = (idx + 1) % hashmap->cells.cap;
    }

    return idx;
}

void ULLStringHashMap_alloc(struct ULLStringHashMap *hashmap, size_t cap) {
    ULLStringHashMap_pair_array_alloc(&hashmap->cells, cap);
    for (size_t i=0; i<hashmap->cells.cap; i++) {
        hashmap->cells.data[i].taken = false;
    }
}

void ULLStringHashMap_free(struct ULLStringHashMap *hashmap) {
    ULLStringHashMap_pair_array_free(&hashmap->cells);
}

void ULLStringHashMap_insert(struct ULLStringHashMap *hashmap, size_t key, const char *value) {
    size_t idx = _ULLStringHashMap_get_idx(hashmap, key);
    hashmap->cells.data[idx].key = key;
    hashmap->cells.data[idx].value = value;
    hashmap->cells.data[idx].taken = true;
}

int main() {
    return 0;
}

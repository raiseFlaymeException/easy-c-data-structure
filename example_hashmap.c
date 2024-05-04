#include <stdio.h>

#include "hashmap/chashmap_creator.h"

size_t hash_fn(size_t key) {
    return key;
}

CHASHMAP_CREATE_DECLARATION(NumberToStringH, size_t, const char *)
CHASHMAP_CREATE_DEFINITION(NumberToStringH, size_t, const char *, hash_fn)


int main() {
    NumberToStringH number_to_name;
    NumberToStringH_alloc(&number_to_name, 6); // use a bigger number (and a prime one)

    if (!NumberToStringH_insert(&number_to_name, 0, "zero")) {
        puts("error inserting 0");
        return 1;
    }

    // if (!NumberToStringH_insert(&hm, 0, "zero")) { // can't insert twice -> this will cause an error
    //     puts("error inserting 0");
    //     return 1;
    // }

    if (!NumberToStringH_insert(&number_to_name, 10, "ten")) {
        puts("error inserting 10");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 20, "twenty")) {
        puts("error inserting 20");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 30, "thirty")) {
        puts("error inserting 30");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 40, "fourty")) {
        puts("error inserting 40");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 50, "fifty")) {
        puts("error inserting 50");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 60, "sixty")) {
        puts("error inserting 60");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 70, "seventy")) {
        puts("error inserting 70");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 80, "eighty")) {
        puts("error inserting 80");
        return 1;
    }
    if (!NumberToStringH_insert(&number_to_name, 90, "ninety")) {
        puts("error inserting 90");
        return 1;
    }

    if (!NumberToStringH_remove(&number_to_name, 0)) {
        puts("error removing 0");
        return 1;
    }
    // if (!NumberToStringH_remove(&hm, 0)) { // can't remove twice -> this will cause an error
    //     puts("failed to remove 0");
    //     return 1;
    // }

    for (size_t i=0; i<10; i++) {
        const char *value;
        if (NumberToStringH_get(&number_to_name, i*10, &value)) {
            printf("%d = %s\n", i*10, value);
        } else {
            printf("%d = no value :(\n", i*10);
            // we don't return because the error is intentional -> the value isn't in out hashmap
        }
    }
    printf("size of number to name: %d\n", number_to_name.size);
    printf("capacity of number to name: %d\n", number_to_name.cap);

    NumberToStringH_free(&number_to_name);
    return 0;
}

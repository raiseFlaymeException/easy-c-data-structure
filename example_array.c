#include "easy_c_data_structure/array/carray_creator.h"

#include <stdio.h>
#include <string.h>

#define SOME_TEXT_CAP 1024

CARRAY_CREATE_DECLARATION(IntArray, int)
CARRAY_CREATE_DEFINITION(IntArray, int)

int main() {
    IntArray int_array;
    IntArray_alloc(&int_array, 1);
    while (1) {
        char some_text[SOME_TEXT_CAP] = {0};
        printf("Enter some number or someting invalid to quit: ");
        if (fgets(some_text, sizeof(some_text), stdin) == NULL) { return EXIT_FAILURE; }
        int result;
        if (sscanf(some_text, "%d", &result) == -1) { break; }

        IntArray_append(&int_array, result);
    }

    for (size_t i = 0; i < int_array.size; i++) {
        printf("some_text %d: %d\n", i, int_array.data[i]);
    }
    printf("IntArray cap: %d\n", int_array.cap);

    IntArray_free(&int_array);
}

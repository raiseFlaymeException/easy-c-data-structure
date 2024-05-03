#ifndef SSTRING_H
#define SSTRING_H

#include <stdio.h>
#include <stdbool.h>

#include "array/carray_creator.h"

// struct StringView {
//     const char *data;
//     size_t size;
// };
// typedef struct StringView StringView;

CARRAY_CREATE_DECLARATION(SString, char)
CARRAY_CREATE_DEFINITION(SString, char)

bool SString_getc_until(SString *str, FILE *file, int char_or_EOF) {
    int cur_char; // can be EOF so int (because sizeof(EOF)>sizeof(char))
    while (true) {
        cur_char = getc(file);
        if (cur_char==EOF) {
            return false;
        }
        if (cur_char==char_or_EOF) {
            return true;
        }
        SString_append(str, cur_char);
    }
}

#endif

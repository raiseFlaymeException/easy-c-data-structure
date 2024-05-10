#include "easy_c_data_structure/simple_string/sstring.h"

#define DEFAULT_STRING_CAP 16

int main() {
    SString string;
    SString_alloc(&string, DEFAULT_STRING_CAP);

    printf("Write someting: ");

    if (!SString_getc_until(&string, stdin, '\n')) {
        printf("error reading stdout");
        return 1;
    }

    printf("You writed: %.*s\n", string.size, string.data);

    SString_free(&string);
    return 0;
}

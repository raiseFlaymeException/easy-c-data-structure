#include "string/sstring.h"


int main() {
    SString string;
    SString_alloc(&string, 16);

    printf("Write someting: ");

    if (!SString_getc_until(&string, stdin, '\n')) {
        printf("error reading stdout");
        return 1;
    }

    printf("You writed: %.*s\n", string.size, string.data);

    SString_free(&string);
    return 0;
}

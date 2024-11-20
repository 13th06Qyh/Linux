#include <stdio.h>
#include <string.h>
#include "greet.h"

static char greeting[100] = "Hello!";

void greet(void) {
    printf("%s\n", greeting);
}

int setgreeting(const char *new_greeting) {
    if (strlen(new_greeting) < sizeof(greeting)) {
        strcpy(greeting, new_greeting);
        return 0;
    }
    return -1;
}

const char* getgreeting(void) {
    return greeting;
}

void hello(const char *name, const char *greeting) {
    printf("%s: %s\n", name, greeting);
}

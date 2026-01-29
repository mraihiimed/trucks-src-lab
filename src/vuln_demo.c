#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 32

// Safe buffer copy using strncpy
void safe_copy(const char *input) {
    char buf[MAX_LEN];
    // Copy at most MAX_LEN - 1 characters and ensure null termination
    strncpy(buf, input, MAX_LEN - 1);
    buf[MAX_LEN - 1] = '\0';
    printf("Copied safely: %s\n", buf);
}

// Safe logging with format specifier
void safe_log(const char *msg) {
    printf("Log: %s\n", msg);
}

// Proper memory allocation and free
void safe_memory_use() {
    char *p = (char*)malloc(16);
    if (!p) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    strncpy(p, "HELLO", 15);
    p[15] = '\0';
    printf("Allocated string: %s\n", p);
    free(p); // freed once, no double free
}

/*int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "DefaultString";

    safe_copy(input);
    safe_log("This is a safe log message");
    safe_memory_use();

    return 0;
}*/


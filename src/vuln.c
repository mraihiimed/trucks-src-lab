#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 16

// --- Unsafe buffer handling ---
void demo_overflow(const char *input) {
    char buf[MAX_LEN];
    // Risk: no bounds check
    strcpy(buf, input);
    printf("Buffer copy result: %s\n", buf);
}

// --- Format string vulnerability ---
void demo_format_string(const char *msg) {
    // Risk: user-controlled string passed directly to printf
    printf(msg);
    printf("\n");
}

// --- Memory misuse examples ---
void demo_double_free() {
    char *p = (char*)malloc(8);
    if (!p) return;
    strcpy(p, "HELLO"); // unsafe copy
    free(p);
    free(p); // double free
}

void demo_use_after_free() {
    char *q = (char*)malloc(12);
    if (!q) return;
    strcpy(q, "WORLD");
    free(q);
    // Risk: accessing freed memory
    printf("Use-after-free: %s\n", q);
}

// --- API misuse examples ---
void demo_null_deref() {
    char *ptr = NULL;
    // Risk: dereferencing NULL pointer
    printf("Null deref: %c\n", *ptr);
}

void demo_unchecked_return() {
    // Risk: ignoring return value of fopen
    FILE *f = fopen("nonexistent.txt", "r");
    char line[32];
    fgets(line, sizeof(line), f); // unsafe if f == NULL
    fclose(f);
}

// --- Main entry point ---
int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "THIS_STRING_IS_TOO_LONG";

    demo_overflow(input);
    demo_format_string("User says: %s");
    demo_double_free();
    demo_use_after_free();
    demo_null_deref();
    demo_unchecked_return();

    return 0;
}

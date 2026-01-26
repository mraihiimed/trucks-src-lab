#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 16

void unsafe_copy(const char *input) {
    char buf[MAX_LEN];
    strcpy(buf, input); // overflow risk
    printf("Copied: %s\n", buf);
}

void unsafe_log(const char *msg) {
    printf(msg); // format string vuln
    printf("\n");
}

void memory_misuse() {
    char *p = (char*)malloc(8);
    if (!p) return;
    strcpy(p, "HELLO"); // no bounds check
    free(p);
    free(p); // double free
}

int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "THIS_STRING_EXCEEDS_16";
    unsafe_copy(input);
    unsafe_log("User says: %s");
    memory_misuse();
    return 0;
}

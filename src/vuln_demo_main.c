#include "vuln_demo.h"

int main(int argc, char **argv) {
    const char *input = (argc > 1) ? argv[1] : "DefaultString";
    safe_copy(input);
    safe_log("This is a safe log message");
    safe_memory_use();
    return 0;
}

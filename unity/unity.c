#include "unity.h"
#include <stdio.h>

// Track test results
static int failures = 0;

void UnityBegin(void) {
    printf("Unity test framework started\n");
    failures = 0;
}

int UnityEnd(void) {
    printf("Unity test framework finished\n");
    if (failures == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d test(s) failed!\n", failures);
    }
    return failures;
}

void RUN_TEST(void (*test)(void), const char* test_name) {
    printf("Running test: %s\n", test_name);
    test();
}

void UnityAssertTrue(int condition, const char* msg, int line) {
    if (!condition) {
        printf("FAIL: %s at line %d\n", msg, line);
        failures++;
    }
}

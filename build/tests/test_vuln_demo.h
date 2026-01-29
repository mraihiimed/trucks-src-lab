#ifndef UNITY_H
#define UNITY_H

// Start and end the test run
void UnityBegin(void);
int UnityEnd(void);

// Run a single test function with a name
void RUN_TEST(void (*test)(void), const char* test_name);

// Assertion helpers
void UnityAssertTrue(int condition, const char* msg, int line);

// Convenience macro for boolean checks
#define TEST_ASSERT_TRUE(condition) UnityAssertTrue((condition), #condition, __LINE__)

#endif // UNITY_H

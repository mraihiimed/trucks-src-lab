#ifndef UNITY_H
#define UNITY_H

void UnityBegin(void);
int UnityEnd(void);
void RUN_TEST(void (*test)(void), const char* test_name);
void UnityAssertTrue(int condition, const char* msg, int line);

// Macro for convenience
#define TEST_ASSERT_TRUE(condition) UnityAssertTrue((condition), #condition, __LINE__)

#endif

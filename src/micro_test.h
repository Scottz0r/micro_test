#ifndef _MICRO_TEST_H_INCLUDE_GUARD
#define _MICRO_TEST_H_INCLUDE_GUARD

/**
    Test a condition. Records a failure if expr is not truthy.

    This should be called between U_TEST_CASE_START and U_TEST_CASE_END to properly record pass/fail statue of a
    single test case.
*/
#define U_TEST(expr) _micro_test(!!(expr), #expr, __FILE__, __func__, __LINE__)

/**
    Like U_TEST, but will exit the current function on failure. Useful for conditions that must be true to do tests,
    like checking for NULL before dereferencing a pointer.

    This assumes that this is used in functions that return void.
*/
#define U_REQUIRE(expr) while(!_micro_require(!!(expr), #expr, __FILE__, __func__, __LINE__))\
    {\
    U_TEST_CASE_END();\
    return;\
    }

/**
    Groups tests into a common test case.
*/
#define U_TEST_CASE_START(name) _micro_test_case_start(name)

/**
    End the current test case. Reports status of test case.
*/
#define U_TEST_CASE_END() _micro_test_case_end()

/**
    Report status of all tests. Will print overall PASS/FAIL message.

    Returns 0 if all tests passed, 1 if any test failed.
*/
#define U_TEST_REPORT() _micro_test_report()

int _micro_test(int result, const char* expr, const char* file, const char* func, int line);

int _micro_require(int result, const char* expr, const char* file, const char* func, int line);

void _micro_test_case_start(const char* name);

void _micro_test_case_end();

int _micro_test_report();

#endif // _MICRO_TEST_H_INCLUDE_GUARD

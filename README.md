# Micro Test (U_TEST)

Very minimal testing framework for C and C++ (but mostly for C).

## Example

```c
#include "micro_test.h"

static void test_example();
static void another_test();

int main(int argc, const char** argv)
{
    test_example();
    another_test();

    return U_TEST_REPORT();
}

static void test_example()
{
    U_TEST_CASE_START("Example test case");

    U_TEST(1 == 1);
    U_TEST(1 == 2);

    int* some_ptr = (void*)0;
    U_REQUIRE(some_ptr);

    U_TEST(*some_ptr == 1);

    U_TEST_CASE_END();
}

static void another_test()
{
    U_TEST_CASE_START("Test Case 2");

    U_TEST(1);
    U_TEST(!0);

    U_TEST_CASE_END();
}

```


Output

```txt
TEST CASE: Example test case
        f: Test failed at /micro_test_example/example.c:19: 1 == 2
        f: Test failed at /micro_test_example/example.c:22: some_ptr
        x: REQUIRE failed. Exiting function.
        > FAILED: 2, TOTAL: 3
TEST CASE: Test Case 2
        > FAILED: 0, TOTAL: 2
---
TEST RESULTS:
Total Test Cases: 2
Total Asserts:    5
Total Failed:     0

FAIL
```

## API

### Overview

There are no magic macros that automatically register and run tests.

Test cases should be placed in a function that returns void. It is left to the user to call functions that contain tests.

### U_TEST(expr)

Tests the expression. If false, reports an error for the current test case.

A warning will be written to stdout if there is no active test case.

### U_REQUIRE(expr)

Tests the expression. If false, reports and error and exits from the current function.

A warning will be written to stdout if there is no active test case.

### U_TEST_CASE_START(name)

Starts a test case. Any `U_TEST` or `U_REQUIRE` used after this statement will be associated with the test case. Pass and fail count will be tracked per test case. Test cases must be ended with `U_TEST_CASE_END`.

A test case should be started before using `U_TEST` and `U_REQUIRE`. A warning will be issued if no active test case is found.

The name will be truncated if it is over 255 characters.

A warning will be written to stdout if there is already an active test case.

### U_TEST_CASE_END()

Ends a test case and prints pass/fail counts for the test case.

A warning will be written to stdout if there is no active test case.

### U_TEST_REPORT()

Prints a summary of tests, including a pass/fail status.

Returns 1 if all tests passed. Otherwise, 0.

## Why Use This?

* You want a test framework that doesn't bloat compile times.
* You need something quick with little to learn.

## Why Not Use This?

* If you need automatic test registration.
* You need automatic setup/teardown.

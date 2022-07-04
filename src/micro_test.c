#include "micro_test.h"

#include <stdio.h>
#include <string.h>

#define U_TEST_CASE_NAME_SIZE 256

typedef struct u_test_case_t
{
    char name[U_TEST_CASE_NAME_SIZE];
    unsigned count_asserts;
    unsigned count_fail;
} u_test_case_t;

typedef struct u_test_state_t
{
    unsigned count_asserts;
    unsigned count_fail;
    unsigned count_test_cases;
} u_test_state_t;

static u_test_case_t s_curr_test;
static u_test_state_t s_test_state;

static void safe_strcpy(char* dst, const char* src, size_t dst_size);
static void prior_state_check();

int _micro_test(int result, const char* expr, const char* file, const char* func, int line)
{
    int retval = 1;

    // Assumption: Within test case.
    if (s_curr_test.name[0] == 0)
    {
        printf("WARNING: assert not in test case\n");
    }

    s_curr_test.count_asserts++;
    s_test_state.count_asserts++;

    if (!result)
    {
        retval = 0;
        printf("\tf: Test failed at %s:%d: %s\n", file, line, expr);
        s_curr_test.count_fail++;
        s_test_state.count_fail++;
    }

    return retval;
}

int _micro_require(int result, const char* expr, const char* file, const char* func, int line)
{
    int retval = _micro_test(result, expr, file, func, line);

    if (!retval)
    {
        printf("\tx: REQUIRE failed. Exiting function.\n");
    }

    return retval;
}

void _micro_test_case_start(const char* name)
{
    // Assumption: Prior test case was ended.
    prior_state_check();

    s_curr_test.count_asserts = 0;
    s_curr_test.count_fail = 0;

    safe_strcpy(s_curr_test.name, name, U_TEST_CASE_NAME_SIZE);

    s_test_state.count_test_cases++;

    printf("TEST CASE: %s\n", name);
}

void _micro_test_case_end()
{
    // Assumption: Test case START called before this.
    if (s_curr_test.name[0] == 0)
    {
        printf("WARNING: END called without matching START\n");
    }

    printf("\t> FAILED: %u, TOTAL: %u\n", s_curr_test.count_fail, s_curr_test.count_asserts);

    s_curr_test.count_asserts = 0;
    s_curr_test.count_fail = 0;
    safe_strcpy(s_curr_test.name, "", U_TEST_CASE_NAME_SIZE);
}

int _micro_test_report()
{
    // Assumption: Test cases are ended before calling this.
    prior_state_check();

    printf("---\n");
    printf("TEST RESULTS:\n");
    printf("Total Test Cases: %u\n", s_test_state.count_test_cases);
    printf("Total Asserts:    %u\n", s_test_state.count_asserts);
    printf("Total Failed:     %u\n", s_curr_test.count_fail);
    printf("\n");

    if (s_test_state.count_fail)
    {
        printf("FAIL\n");
    }
    else
    {
        printf("PASS\n");
    }

    return (s_test_state.count_fail > 0);
}

/**
    Copy a string without worrying about buffer overflow. Assumes src is null terminated.
*/
static void safe_strcpy(char* dst, const char* src, size_t dst_size)
{
    for(size_t i = 0; i < dst_size; ++i)
    {
        dst[i] = src[i];

        if (*src == 0)
        {
            break;
        }
    }
}

/**
    Check if there is a current test active. Reports warning.
*/
static void prior_state_check()
{
    if (s_curr_test.count_asserts > 0)
    {
        printf("WARNING: prior test case not ended\n");
    }
}

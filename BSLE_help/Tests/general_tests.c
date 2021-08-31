#include "../INCLUDE/{Header of files to test"
#include <stdlib.h>
//#include <CUnit/CUnitCI.h>
#include <CUnit/CUnit.h>

/*
    Reference the CUnit Users Guide:
    http://cunit.sourceforge.net/doc/writing_tests.html#tests

    Step 1. Create the test cases
    Step 2. _add the test suite to the registry
    Step 3. _add the test to the suite.
*/

#define RAND_RANGE(lower, upper) ((rand() % (upper - lower + 1)) + lower)

void test_something()

void jqr_test_fresh_int_pointer(void)
{
    int *fresh = fresh_int_pointer();
    CU_ASSERT_PTR_NULL(fresh);
}

void jqr_test_get_value(void)
{
    int value = rand();
    int value2 = get_value(&value);
    CU_ASSERT_EQUAL(value2, value);
}

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Automated.h>
#include <CUnit/Basic.h>
//#include <CUnit/CUnitCI.h>
#include "general_tests.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if (CUE_SUCCESS != CU_initialize_registry())
    {
        return CU_get_error();
    }
    CU_pSuite general_test_suite = CU_add_suite("General_Tests", NULL, NULL);

    if (NULL == general_test_suite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(general_test_suite, "test of something", test_something)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);

    if (argc >= 1)
    {
        CU_set_output_filename(argv[0]);
    }

    CU_automated_enable_junit_xml(CU_TRUE);
    CU_automated_run_tests();
    CU_list_tests_to_file();

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

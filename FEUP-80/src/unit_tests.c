#include "unit_tests.h"
#include "unity.h"

int Counter;

void setUp(void)
{
  //This is run before EACH TEST
  Counter = 0x5a5a;
}

void tearDown(void)
{
}


int bar()
{
    return 0;
}

int foo()
{
    TEST_ASSERT_EQUAL(13, bar());
}

void run_test_suite()
{
    suiteSetUp();
    foo();
}

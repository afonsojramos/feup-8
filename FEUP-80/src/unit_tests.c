#include "unit_tests.h"
#include "tinytest.h"

/* All FEUP-8 headers below this line */
#include "net.h"

/**
  * Simple example showing all assertions
  * The tests stop running immediately after the first error,
  * so all failures are commented
  */
void testExample()
{
    //equality assert for numbers and references
    ASSERT_EQUALS(12, 12);  //PASS
    //ASSERT_EQUALS(12, 13);  //FAIL

    //equality assert for strings
    ASSERT_STRING_EQUALS("Hello", "Hello");     //PASS
    //ASSERT_STRING_EQUALS("Hello", "Goodbye");   //FAIL
}

/*All test functions below this line*/

void testNet()
{
    Net* net = createNet();
    ASSERT_EQUALS(TRUE, net != NULL);
}

/*End of test functions*/

int run_test_suite()
{
    //All test functions should be added here with the RUN macro
    RUN(testExample);
    RUN(testNet);
    return TEST_REPORT();
}

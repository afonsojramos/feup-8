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

extern char *auth_token;
#include "web_comunication_api.h"
/* web_comunication_api tests */
void testLoginRequest()
{
    //correct login
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"auth_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\"}";
    int ret = loginRequestSend("user", "pwd", true, mock_response_data);
    char *data_sent_to_server = mock_response_data;
    ASSERT_STRING_EQUALS(data_sent_to_server, "username=user&password=pwd");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);
    
    //wrong password
    mock_response_data = 
    "{        \"response_code\": 1    }";
    ret = loginRequestSend("user", "pwd", true, mock_response_data);
    data_sent_to_server = mock_response_data;
    ASSERT_STRING_EQUALS(data_sent_to_server, "username=user&password=pwd");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, WRONG_CREDENTIALS);
}

/*End of test functions*/

int run_test_suite()
{
    //All test functions should be added here with the RUN macro
    RUN(testExample);
    RUN(testNet);
    return TEST_REPORT();
}

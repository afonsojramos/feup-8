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

    printf("testNet: OK\n");
}

extern char *auth_token;
extern char *server_address;
extern int server_port;
#include "web_comunication_api.h"
/* web_comunication_api tests */
void testLoginRequest()
{
    //correct login
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"auth_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\"}";

    char *mock_response_data_ = malloc(strlen(mock_response_data) + 1);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    int ret = loginRequestSend("user", "pwd", true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "username=user&password=pwd");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);    
    
    //wrong password
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = loginRequestSend("user", "pwd", true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "username=user&password=pwd");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, WRONG_CREDENTIALS);

    //response data with non-parsable json
    mock_response_data = 
        "INVALID JSON STUFF";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = loginRequestSend("user", "pwd", true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "username=user&password=pwd");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testLoginRequest: OK\n");
}

void testRegisterRequest()
{
    //correct login
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"auth_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\"}";
    char *mock_response_data_ = malloc(strlen(mock_response_data) + 1);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    int ret = registerRequestSend("mister X", "misterx@testing.com", "user", "pwd", true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "name=mister X&email=misterx@testing.com&username=user&password=pwd");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);
    
    //wrong password
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = registerRequestSend("mister X", "misterx@testing.com", "user", "pwd", true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "name=mister X&email=misterx@testing.com&username=user&password=pwd");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);

    //response data with non-parsable json
    mock_response_data = 
        "INVALID JSON STUFF";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = registerRequestSend("mister X", "misterx@testing.com", "user", "pwd", true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "name=mister X&email=misterx@testing.com&username=user&password=pwd");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testRegisterRequest: OK\n");
}

void testLogoutRequest()
{
    char *auth_token_ = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    auth_token = malloc(strlen(auth_token_) + 1);
    memcpy(auth_token, auth_token_, strlen(auth_token_));
    auth_token[strlen(auth_token_)] = '\0';
    //correct login
    char *mock_response_data = 
    "{    \"response_code\": 0   }";
    char *mock_response_data_ = malloc(5000);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data));
    mock_response_data_[strlen(mock_response_data)] = '\0';
    int ret = logoutRequestSend(true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    char *data_sent_to_server_correct = "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n";
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_EQUALS(auth_token, NULL);
    ASSERT_EQUALS(ret, SUCCESS);
    
    //wrong password
    auth_token = malloc(strlen(auth_token_) + 1);
    memcpy(auth_token, auth_token_, strlen(auth_token_));
    auth_token[strlen(auth_token_)] = '\0';
    char *mock_response_data2 = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data2, strlen(mock_response_data2));
    mock_response_data_[strlen(mock_response_data2)] = '\0';
    ret = logoutRequestSend(true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);

    printf("testLogoutRequest: OK\n");
}

void testGetExercisesListRequest()
{
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    //correct login
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"exercises\": [        {            \"id\": \"1\",            \"title\": \"sit amet metus.\",            \"progress\": \"0\"        },        {            \"id\": \"2\",            \"title\": \"ac mattis semper,\",            \"progress\": \"10\"        },        {            \"id\": \"3\",            \"title\": \"magnis dis parturient\",            \"progress\": \"44\"        }    ]    }";
    char *mock_response_data_ = malloc(strlen(mock_response_data) + 1);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ExerciseSimplified *exercises_list;
    size_t number_of_exercises;
    int ret = getExercisesListRequestSend(&exercises_list, &number_of_exercises, true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);

    //build array with correct exercises
    ExerciseSimplified exercises_list_correct[3];
    ExerciseSimplified exercise_correct;

    exercise_correct.id = 1;
    exercise_correct.title = "sit amet metus.";
    exercise_correct.progress = 0;
    exercises_list_correct[0] = exercise_correct;

    exercise_correct.id = 2;
    exercise_correct.title = "ac mattis semper,";
    exercise_correct.progress = 10;
    exercises_list_correct[1] = exercise_correct;

    exercise_correct.id = 3;
    exercise_correct.title = "magnis dis parturient";
    exercise_correct.progress = 44;
    exercises_list_correct[2] = exercise_correct;

    //test if the array was filled correctly
    ASSERT_EQUALS(number_of_exercises, 3);

    ASSERT_EQUALS(exercises_list_correct[0].id, exercises_list[0].id);
    ASSERT_STRING_EQUALS(exercises_list_correct[0].title, exercises_list[0].title);
    ASSERT_EQUALS(exercises_list_correct[0].progress, exercises_list[0].progress);
    
    ASSERT_EQUALS(exercises_list_correct[1].id, exercises_list[1].id);
    ASSERT_STRING_EQUALS(exercises_list_correct[1].title, exercises_list[1].title);
    ASSERT_EQUALS(exercises_list_correct[1].progress, exercises_list[1].progress);
    
    ASSERT_EQUALS(exercises_list_correct[2].id, exercises_list[2].id);
    ASSERT_STRING_EQUALS(exercises_list_correct[2].title, exercises_list[2].title);
    ASSERT_EQUALS(exercises_list_correct[2].progress, exercises_list[2].progress);

    //wrong password
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = getExercisesListRequestSend(&exercises_list, &number_of_exercises, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);


    //response array without some id's
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
        "{    \"response_code\": 0,    \"exercises\": [        {            \"id\":true,            \"title\": \"sit amet metus.\",            \"progress\": \"0\"        },        {            \"id\": \"2\",            \"title\": \"ac mattis semper,\",            \"progress\": \"10\"        },        {            \"id\": \"3\",            \"title\": \"magnis dis parturient\",            \"progress\": \"44\"        }    ]    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = getExercisesListRequestSend(&exercises_list, &number_of_exercises, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    //response array with some id's equal to 0
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
        "{    \"response_code\": 0,    \"exercises\": [        {            \"id\": \"0\",            \"title\": \"sit amet metus.\",            \"progress\": \"0\"        },        {            \"id\": \"2\",            \"title\": \"ac mattis semper,\",            \"progress\": \"10\"        },        {            \"id\": \"3\",            \"title\": \"magnis dis parturient\",            \"progress\": \"44\"        }    ]    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = getExercisesListRequestSend(&exercises_list, &number_of_exercises, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    //response data with non-parsable json
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
        "INVALID JSON STUFF";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = getExercisesListRequestSend(&exercises_list, &number_of_exercises, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testGetExercisesListRequest: OK\n");
}

void testGetExerciseDetailsRequest()
{
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    //correct login
    int exercise_id = 26;
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"exercise\": [        {            \"title\": \"ac mattis semper,\",            \"description\": \"Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam\",            \"image_base64\": \"2.png\",            \"creator_name\": \"Utilizador Um\",            \"progress\": \"10\",            \"feup8_file\": \"c2R0aCB0c2h0c2VyeTR3dGFiMzQ2cTUzNHkgNjR1cyA1NnNyNHU=\"        }    ],    \"tests\": [        {            \"id\": \"2\",            \"title\": \"consequat purus. Maecenas\",            \"test_code\": \"c2RmIHpkZiBnZGZnIGZzZGd2c3RmZHZzZXJ0dnNkdGZ2dmR0ZiBzZXJ0dnNlcnR2NnczdjU0\",            \"hint\": \"at lacus. Quisque purus sapien,\"        }    ]    };    ";
    char *mock_response_data_ = malloc(5000);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    tic_exercise exercise;
    int ret = getExerciseDetailsRequestSend(exercise_id, &exercise, true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);

    //build correct exercise
    tic_exercise exercise_correct;
    exercise_correct.exerciseTests = malloc(sizeof(ExerciseTest));

    //fil in exercise details
    exercise_correct.title = "ac mattis semper,";
    exercise_correct.creator_name = "Utilizador Um";
    exercise_correct.description = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam";
    //exercise_correct.img_base64 = "2.png";
    exercise_correct.progress = 10;
    exercise_correct.feup8_file.data = "sdth tshtsery4wtab346q534y 64us 56sr4u";
    exercise_correct.feup8_file.size = 38;
    
    
    //fill in test details
    exercise_correct.exerciseTests->id = 2;
    exercise_correct.exerciseTests->title = "consequat purus. Maecenas";
    exercise_correct.exerciseTests->test_code = "sdf zdf gdfg fsdgvstfdvsertvsdtfvvdtf sertvsertv6w3v54";
    exercise_correct.exerciseTests->hint = "at lacus. Quisque purus sapien,";
    
    //test if the exercise and exercise tests were filled correctly
    ASSERT_STRING_EQUALS(exercise_correct.title, exercise.title);
    ASSERT_STRING_EQUALS(exercise_correct.creator_name, exercise.creator_name);
    ASSERT_STRING_EQUALS(exercise_correct.description, exercise.description);
    ASSERT_STRING_EQUALS(exercise_correct.feup8_file.data, exercise.feup8_file.data);
    ASSERT_EQUALS(exercise_correct.feup8_file.size, exercise.feup8_file.size);
    
    ASSERT_EQUALS(exercise_correct.exerciseTests->id, exercise.exerciseTests->id);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->title, exercise.exerciseTests->title);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->test_code, exercise.exerciseTests->test_code);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->hint, exercise.exerciseTests->hint);
    
    //wrong password
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = getExerciseDetailsRequestSend(exercise_id, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);

    printf("testGetExerciseDetailsRequest: OK\n");
}

void testSaveProgressRequest()
{
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    //correct login
    int exercise_id = 26;
    char *mock_response_data = 
    "{    \"response_code\": 0};    ";
    char *mock_response_data_ = malloc(5000);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    Buffer exercise_data;
    exercise_data.data = "asdfdb dfg df sge3rt 34 rt4werty ewrty 354qty 3r5 t4erg erfg ";
    exercise_data.size = 61;
    char *code = "if (stuff) then a; else b;";
    int ret = saveProgressRequestSend(exercise_data, code, 2, true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);
    
    //assert that data sent to server is correct
    char *headers_sent_to_server = "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n";
    char *exercise_data_and_code_sent_to_server_correct = "exercise_data=YXNkZmRiIGRmZyBkZiBzZ2UzcnQgMzQgcnQ0d2VydHkgZXdydHkgMzU0cXR5IDNyNSB0NGVyZyBlcmZnIA==&code=aWYgKHN0dWZmKSB0aGVuIGE7IGVsc2UgYjs=";
    
    char *data_sent_to_server_correct = malloc(5000);
    memcpy(data_sent_to_server_correct, headers_sent_to_server, strlen(headers_sent_to_server) + 1);
    strcat(data_sent_to_server_correct, "\n\n");
    strcat(data_sent_to_server_correct, exercise_data_and_code_sent_to_server_correct);
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);


    //wrong password
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = saveProgressRequestSend(exercise_data, code, 2, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);

    //response data with non-parsable json
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
        "INVALID JSON STUFF";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = saveProgressRequestSend(exercise_data, code, 2, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testSaveProgressRequest: OK\n");
}

void testSendCodeToServerAndGetTestsResultsRequestSend()
{
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    //correct login
    int exercise_id = 26;
    char *mock_response_data = 
    "{    \"response_code\": 0,  \"tests_global_state\": 0,	\"tests_results\":	{		\"test1_title\": true, \"test2_title\": false	}  }";

    char *mock_response_data_ = malloc(5000);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);



    
    //build correct exercise
    tic_exercise exercise;
    exercise.exerciseTests = malloc(sizeof(ExerciseTest) * 2);

    //fil in exercise details
    exercise.title = "ac mattis semper,";
    exercise.creator_name = "Utilizador Um";
    exercise.description = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam";
    //exercise_correct.img_base64 = "2.png";
    exercise.progress = 10;
    exercise.feup8_file.data = "sdth tshtsery4wtab346q534y 64us 56sr4u";
    exercise.feup8_file.size = 38;
    exercise.number_of_exercise_tests = 2;
    
    
    //fill in test details
    exercise.exerciseTests[0].id = 2;
    exercise.exerciseTests[0].title = "test1_title";
    exercise.exerciseTests[0].test_code = "sdf zdf gdfg fsdgvstfdvsertvsdtfvvdtf sertvsertv6w3v54";
    exercise.exerciseTests[0].hint = "at lacus. Quisque purus sapien,";
    exercise.exerciseTests[0].passed = false;

    
    exercise.exerciseTests[1].id = 4;
    exercise.exerciseTests[1].title = "test2_title";
    exercise.exerciseTests[1].test_code = "sdf zdf gdfg fsdgvstfdvsertvsdtfvvdtf sertvsertv6w3v54";
    exercise.exerciseTests[1].hint = "at lacus. Quisque purus sapien,";
    exercise.exerciseTests[1].passed = true;


    //build correct exercise
    tic_exercise exercise_correct;
    exercise_correct.exerciseTests = malloc(sizeof(ExerciseTest));

    //fil in exercise details
    exercise_correct.title = "ac mattis semper,";
    exercise_correct.creator_name = "Utilizador Um";
    exercise_correct.description = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam";
    //exercise_correct.img_base64 = "2.png";
    exercise_correct.progress = 10;
    exercise_correct.feup8_file.data = "sdth tshtsery4wtab346q534y 64us 56sr4u";
    exercise_correct.feup8_file.size = 38;
    
    
    //fill in test details
    exercise_correct.exerciseTests->id = 2;
    exercise_correct.exerciseTests->title = "test1_title";
    exercise_correct.exerciseTests->test_code = "sdf zdf gdfg fsdgvstfdvsertvsdtfvvdtf sertvsertv6w3v54";
    exercise_correct.exerciseTests->hint = "at lacus. Quisque purus sapien,";
    exercise_correct.exerciseTests->passed = true;
    
    char *code = "if (stuff) then a; else b;";
    int ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);
    
    //assert that data sent to server is correct
    char *headers_sent_to_server = "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n";
    char *exercise_data_and_code_sent_to_server_correct = "code=aWYgKHN0dWZmKSB0aGVuIGE7IGVsc2UgYjs=";
    
    char *data_sent_to_server_correct = malloc(5000);
    memcpy(data_sent_to_server_correct, headers_sent_to_server, strlen(headers_sent_to_server) + 1);
    strcat(data_sent_to_server_correct, "\n\n");
    strcat(data_sent_to_server_correct, exercise_data_and_code_sent_to_server_correct);
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);


    //test if the exercise and exercise tests were not changed by this function
    ASSERT_STRING_EQUALS(exercise_correct.title, exercise.title);
    ASSERT_STRING_EQUALS(exercise_correct.creator_name, exercise.creator_name);
    ASSERT_STRING_EQUALS(exercise_correct.description, exercise.description);
    ASSERT_STRING_EQUALS(exercise_correct.feup8_file.data, exercise.feup8_file.data);
    ASSERT_EQUALS(exercise_correct.feup8_file.size, exercise.feup8_file.size);
    
    ASSERT_EQUALS(exercise_correct.exerciseTests->id, exercise.exerciseTests->id);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->title, exercise.exerciseTests->title);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->test_code, exercise.exerciseTests->test_code);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTests->hint, exercise.exerciseTests->hint);    
    ASSERT_EQUALS(exercise_correct.exerciseTests->passed, exercise.exerciseTests->passed);
    

    //tests failing
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 0,      \"tests_global_state\": -1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SYNTACTIC_ERRORS);

    //tests failing
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 0,      \"tests_global_state\": -2    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, EXECUTION_TIMEOUT);

    //wrong password
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 1    }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);

 	//response data with non-parsable json
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
        "INVALID JSON STUFF";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

 	//tests_global_state doesn't exist causing a null
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 0   }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    //tests_results doesn't exist causing a null
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{        \"response_code\": 0,   \"tests_global_state\": 0     }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    //result_obj of a test doesn't exist causing a null
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    mock_response_data = 
    "{    \"response_code\": 0,  \"tests_global_state\": 0,	\"tests_results\":	{		\"test1_title_not_existent\": true, \"test2_title\": false	}  }";
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    ret = sendCodeToServerAndGetTestsResultsRequestSend(2, code, &exercise, true, mock_response_data_);
    data_sent_to_server = mock_response_data_;
    //assert that the function does not change the auth_token if the login is not successful
    ASSERT_STRING_EQUALS(data_sent_to_server, data_sent_to_server_correct);
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testSendCodeToServerAndGetTestsResultsRequestSend: OK\n");
}

/**
* This method tests if the method setAllTestsAsValue sets the value "passed" of all tests of the exercise given as parameter
*/
void testSetAllTestsAsValue()
{
    //assuming an exercise with 5 tests
    tic_exercise ticExercise;
    ticExercise.number_of_exercise_tests = 5;
    ExerciseTest *exerciseTests = malloc(sizeof(ExerciseTest) * ticExercise.number_of_exercise_tests);
    ticExercise.exerciseTests = exerciseTests;

    int value = 0;
    setAllTestsAsValue(&ticExercise, value);
    for(int i = 0; i < ticExercise.number_of_exercise_tests; i++)
    {
        ASSERT_EQUALS(ticExercise.exerciseTests[i].passed, value); 
    } 

    printf("testSetAllTestsAsValue: OK\n");
}

/**
* This function if tests if the function parseExerciseTestsReceived performs correctly when there are errors on the input and returns acordingly
*/
void testParseExerciseTestsReceived()
{
    //exercise tests with non-parsable json
    char *exercise_tests = 
        "INVALID JSON STUFF";
    
    cJSON *obj = cJSON_Parse(exercise_tests);
    tic_exercise exe;
    int ret = parseExerciseTestsReceived(obj, &exe);
    ASSERT_EQUALS(ret, SERVER_ERROR);

    printf("testParseExerciseTestsReceived: OK\n");
}

/**
* This function if tests if the function getStringAfterEqualSymbol performs correctly, i.e. it return the string after the '=' character
*/
void testGetStringAfterEqualSymbol()
{
    //string of which substring will be extracted
    char *string_value = "key=value";
    char *string = malloc(sizeof(char) * (strlen(string_value) + 1));
    sprintf(string, "%s", string_value);
    
    getStringAfterEqualSymbol(&string);
    ASSERT_STRING_EQUALS(string, "value");

    printf("testGetStringAfterEqualSymbol: OK\n");
}

/**
* This function if tests if the function loadServerConfigsFromFile performs correctly, i.e. reading both server address and port from file.
*/
void testLoadServerConfigsFromFile()
{
    //path to file with configs to be read. Two paths can be applied according to if just are being runned tests, or also coverage. 
    //This happens beacuse coverage uses as root the root of project and just run_tests uses as rro the /bin folder
    char *conf_file_path_run_tests = "../conf_test.ini";
    char *conf_file_path_for_coverage = "conf_test.ini";
    char *conf_file_path_run_tests_empty = "../conf_test_empty.ini";
    char *conf_file_path_for_coverage_empty = "conf_test_empty.ini";
    char *conf_file_path_run_tests_just_one_line = "../conf_test_just_one_line.ini";
    char *conf_file_path_for_coverage_just_one_line = "conf_test_just_one_line.ini";


    //file not exists
    int ret = loadServerConfigsFromFile("fileNotExistentPath");
    ASSERT_EQUALS(ret, -2); //fail

    //empty file
    ret = loadServerConfigsFromFile(conf_file_path_run_tests_empty);
    if(ret != -1)
        ret = loadServerConfigsFromFile(conf_file_path_for_coverage_empty);
    ASSERT_EQUALS(ret, -1); //fail

    //file with just one line
    ret = loadServerConfigsFromFile(conf_file_path_run_tests_just_one_line);
    if(ret != -1)
        ret = loadServerConfigsFromFile(conf_file_path_for_coverage_just_one_line);
    ASSERT_EQUALS(ret, -1); //fail

    //correct file
    ret = loadServerConfigsFromFile(conf_file_path_run_tests);
    if(ret != 0)
        ret = loadServerConfigsFromFile(conf_file_path_for_coverage);
    ASSERT_EQUALS(ret, 0); //success

    //assert configs are read and set correctly
    ASSERT_STRING_EQUALS(server_address, "127.0.0.1");
    ASSERT_EQUALS(server_port, 8000);

    printf("testLoadServerConfigsFromFile: OK\n");
}

/**
* This function if tests if the function setNullTerminatorAtFirstCarriageReturnOrLineFeed performs correctly, i.e. placing the string until the first \r or \n.
*/
void testSetNullTerminatorAtFirstCarriageReturnOrLineFeed()
{
    char *stringWithLineFeedOnStack = "string\n";
    char *stringWithCarrigeReturnOnStack = "string\r";
    char *stringWithLineFeedCarrigeReturnOnStack = "string\n\r";
    char *stringWithCarrigeReturnLineFeedOnStack = "string\r\n";

    char *stringWithLineFeed = malloc(strlen(stringWithLineFeedOnStack) + 1);
    memcpy(stringWithLineFeed, stringWithLineFeedOnStack, strlen(stringWithLineFeedOnStack) + 1);
    char *stringWithCarrigeReturn = malloc(strlen(stringWithCarrigeReturnOnStack) + 1);
    memcpy(stringWithCarrigeReturn, stringWithCarrigeReturnOnStack, strlen(stringWithCarrigeReturnOnStack) + 1);
    char *stringWithLineFeedCarrigeReturn = malloc(strlen(stringWithLineFeedCarrigeReturnOnStack) + 1);
    memcpy(stringWithLineFeedCarrigeReturn, stringWithLineFeedCarrigeReturnOnStack, strlen(stringWithLineFeedCarrigeReturnOnStack) + 1);
    char *stringWithCarrigeReturnLineFeed = malloc(strlen(stringWithCarrigeReturnLineFeedOnStack) + 1);
    memcpy(stringWithCarrigeReturnLineFeed, stringWithCarrigeReturnLineFeedOnStack, strlen(stringWithCarrigeReturnLineFeedOnStack) + 1);
    
    setNullTerminatorAtFirstCarriageReturnOrLineFeed(stringWithLineFeed);
    setNullTerminatorAtFirstCarriageReturnOrLineFeed(stringWithCarrigeReturn);
    setNullTerminatorAtFirstCarriageReturnOrLineFeed(stringWithLineFeedCarrigeReturn);
    setNullTerminatorAtFirstCarriageReturnOrLineFeed(stringWithCarrigeReturnLineFeed);

    //assert expected string is "string" for all
    ASSERT_STRING_EQUALS(stringWithLineFeed, "string");
    ASSERT_STRING_EQUALS(stringWithCarrigeReturn, "string");
    ASSERT_STRING_EQUALS(stringWithLineFeedCarrigeReturn, "string");
    ASSERT_STRING_EQUALS(stringWithCarrigeReturnLineFeed, "string");

    printf("testSetNullTerminatorAtFirstCarriageReturnOrLineFeed: OK\n");
}


/*End of test functions*/

int run_test_suite()
{
    //All test functions should be added here with the RUN macro
    RUN(testExample);
    RUN(testNet);
    RUN(testLoginRequest);
    RUN(testRegisterRequest);
    RUN(testLogoutRequest);
    RUN(testGetExercisesListRequest);
    RUN(testGetExerciseDetailsRequest);
    RUN(testSaveProgressRequest);
    RUN(testSendCodeToServerAndGetTestsResultsRequestSend);
    RUN(testSetAllTestsAsValue);
    RUN(testParseExerciseTestsReceived);
    RUN(testGetStringAfterEqualSymbol);
    RUN(testLoadServerConfigsFromFile);
    RUN(testSetNullTerminatorAtFirstCarriageReturnOrLineFeed);
    
    return TEST_REPORT();
}
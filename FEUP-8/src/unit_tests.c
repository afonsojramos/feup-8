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
    //ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, FORBIDDEN);
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
}

void testGetExerciseDetailsRequest()
{
    auth_token = "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A";
    //correct login
    int exercise_id = 26;
    char *mock_response_data = 
    "{    \"response_code\": 0,    \"exercise\": [        {            \"title\": \"ac mattis semper,\",            \"description\": \"Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam\",            \"image_base64\": \"2.png\",            \"creator_name\": \"Utilizador Um\",            \"progress\": \"10\",            \"feup8_file\": \"cvb\"        }    ],    \"tests\": [        {            \"id\": \"2\",            \"title\": \"consequat purus. Maecenas\",            \"test_code\": \"c2RmIHpkZiBnZGZnIGZzZGd2c3RmZHZzZXJ0dnNkdGZ2dmR0ZiBzZXJ0dnNlcnR2NnczdjU0\",            \"hint\": \"at lacus. Quisque purus sapien,\"        }    ]    };    ";
    char *mock_response_data_ = malloc(5000);
    memcpy(mock_response_data_, mock_response_data, strlen(mock_response_data) + 1);
    tic_exercise exercise;
    int ret = getExerciseDetailsRequestSend(exercise_id, &exercise, true, mock_response_data_);
    char *data_sent_to_server = mock_response_data_;printf("ret: %d\n", ret);
    ASSERT_STRING_EQUALS(data_sent_to_server, "Accept: application/json\r\nAuthorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A\r\n");
    ASSERT_STRING_EQUALS(auth_token, "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjY0MjA4NmVlY2QxNDEwODk1MDU0MzliNWZjNzM3NTFhZTU1ZTdkNzg0Y2Q0OTdkMTNiOWJjNDcwN2Q1NmNlMDVkYTRkNzI0M2ZmYWFiNDcwIn0.eyJhdWQiOiIxIiwianRpIjoiNjQyMDg2ZWVjZDE0MTA4OTUwNTQzOWI1ZmM3Mzc1MWFlNTVlN2Q3ODRjZDQ5N2QxM2I5YmM0NzA3ZDU2Y2UwNWRhNGQ3MjQzZmZhYWI0NzAiLCJpYXQiOjE1NDA3NDQwMDAsIm5iZiI6MTU0MDc0NDAwMCwiZXhwIjoxNTcyMjgwMDAwLCJzdWIiOiIxIiwic2NvcGVzIjpbXX0.Uto9ype4cBVvbdztPT5pO_GsMouBgPH8MN-AX5O9AxlxjQ9H6xjstrOJMxMhsd1d6ni6aUcZAMtCiX2VjopxaRncEIcSTeLLduNjXedarkNa7_7xmzFPr8dfj20w9-4bRJ5fxzRkJj8qFFpaV21YYZghCyKJs8b0Wbhs77X1xAh7oVv2VWH5h_7o7dzc49ueRpXFPLcZukgCxpMBeTKnH7oN-v7GckGcvJiTJmdLt6moKAUCxjgpqGml8Tkyzc7PaKCYwA7PQ0UVBWFtBJQz85vRnpLmm7froF95Ra0eQulbrgeLvARaJ76U37Ht_mUz3trlmRsWBHoAlexx5QlWCdjWtYMw5Y1i-BtYWZdnHwSOGDkprQKU-ZB-hNlVFCrNIbSnhuaPqifzo82PjfKrYNffl5l2-DoquNTvga7Vr62WWKwQAEMuVW_YyfPslBb_FBowIXcYwwv-HYDz9xq6MWtbePH8-ju-pDO-T4TAdvPGf0d-mG9DdpQVZhGGZl7yh0riB4tCbYLm_VAtcuEfqgDgI1eZeoVyDWosJ34wXfIFTXn4ptEYMwQLhXmEIoFGcgc_S1pp1VtEMxk42BfTlgRUnqVmjtBYLQxgv8FQAd92jug-R5_FKFulAX9AaRt_sZcJULr2DnCHQmm_AoTJVb0xSBZYW_3WKPYDSMXSw_A");
    ASSERT_EQUALS(ret, SUCCESS);

    //build correct exercise
    tic_exercise exercise_correct;
    exercise_correct.exerciseTest = malloc(sizeof(ExerciseTest));

    //fil in exercise details
    exercise_correct.title = "ac mattis semper,";
    exercise_correct.creator_name = "Utilizador Um";
    exercise_correct.description = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat. Etiam";
    //exercise_correct.img_base64 = "2.png";
    exercise_correct.progress = 10;
    //exercise_correct.feup8_file = "";
    
    //fill in test details
    exercise_correct.exerciseTest->id = 2;
    exercise_correct.exerciseTest->title = "consequat purus. Maecenas";
    exercise_correct.exerciseTest->test_code = "sdf zdf gdfg fsdgvstfdvsertvsdtfvvdtf sertvsertv6w3v54";
    exercise_correct.exerciseTest->hint = "at lacus. Quisque purus sapien,";
    
    //test if the exercise and exercise tests were filled correctly
    ASSERT_STRING_EQUALS(exercise_correct.title, exercise.title);
    ASSERT_STRING_EQUALS(exercise_correct.creator_name, exercise.creator_name);
    ASSERT_STRING_EQUALS(exercise_correct.description, exercise.description);
    ASSERT_EQUALS(exercise_correct.progress, exercise.progress);
    
    ASSERT_EQUALS(exercise_correct.exerciseTest->id, exercise.exerciseTest->id);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTest->title, exercise.exerciseTest->title);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTest->test_code, exercise.exerciseTest->test_code);
    ASSERT_STRING_EQUALS(exercise_correct.exerciseTest->hint, exercise.exerciseTest->hint);
    
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
    return TEST_REPORT();
}

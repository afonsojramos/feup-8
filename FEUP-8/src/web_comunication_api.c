#include "web_comunication_api.h"
#include "base64_enc_dec.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int printDebugMsg()
{
    static int count = 1;
    printf("debug number %d\n", count);
    count++;
}

/**
* Global variable that contains the token of the session. Is filled when login, and destroyed in logout.
*/
static char *auth_token = NULL;

/**
* Creates a string with the additional header parameters where auth_token is placed according to laravel.
* @return A string, additional header string. 
*/
char *getAdditionalHeaderStringWithAuthToken()
{
    const char *accept = "Accept";
    const char *app_json = "application/json";
    char *first_parameter = buildHttpParameter(accept, app_json);

    const char *auth = "Authorization";
    char *bearer_str = "Bearer ";
    char *bearer = concateStrings(bearer_str, auth_token);
    char *second_parameter = buildHttpParameter(auth, bearer);
    char *additional_header = concateStrings(first_parameter, second_parameter);
    free(second_parameter);
    return additional_header;
}

/**
* Creates a copy of the original string in the heap using malloc.
* @param original, the original string to be copied.
* @return A string, a copy of the orginal string. 
*/
static char* getStringCopy(const char *original)
{
    size_t copySize = sizeof(char) * (strlen(original) + 1);
    char *copy = malloc(copySize);
    memcpy(copy, original, copySize);

    return copy;
}


/**
* Creates login request and sends it to the web server. Returns an int code indentifying the result of the request.
* @param username The username to login with.
* @param password The password to login with.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 1 - wrong username or password.
* 2 - server error.
* 3 - can't connect to server.
* Login request is type POST to /login
* Example: username=up201683756&password=studentblabla
*/
int loginRequest(const char *username, const char *password)
{
    Buffer dataToSend;
    int FIXED_LOGIN_MESSAGE_SIZE = 19;
    dataToSend.size = strlen(username) + strlen(password) + FIXED_LOGIN_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "username=%s&password=%s", username, password);
    Buffer response = sendHttpPostRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, LOGIN_PATH, &dataToSend, NULL, CONNECTION_TIMEOUT_MS);
    if(response.data == NULL)
        return 3;
    
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(dataToSend.data);
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == 0)
    {
        cJSON *auth_token_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "auth_token");
        if(auth_token_obj == NULL)
            return 2;
        char *auth_token_str = auth_token_obj->valuestring;
        if(auth_token_str == NULL)
            return 2;
        auth_token = getStringCopy(auth_token_str);
        cJSON_free(auth_token_obj);
    }
    free(dataToSend.data);
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    return ret_code; //can display a message saying what hapenned and return acordingly
}



/**
* Creates register request and sends it to the web server. Returns an int code indentifying the result of the request.
* @param name The name to register with.
* @param email The email to register with.
* @param username The username to register with.
* @param password The password to register with.
* @param auth_token The authentication token received from server. A pointer to a (char pointer (previously allocated)) should be passed as parameter.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - server error.
* 3 - can't connect to server.
* register request is type POST to /register
* Example: name=Student X&email=up201683756@fe.up.pt&username=up201683756&password=studentblabla
*/
int registerRequest(const char *name, const char *email, const char *username, const char *password)
{
    Buffer dataToSend;
    int FIXED_REGISTER_MESSAGE_SIZE = 32;
    dataToSend.size = strlen(name) + strlen(email) + strlen(username) + strlen(password) + FIXED_REGISTER_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "name=%s&email=%s&username=%s&password=%s",
            name, email, username, password);
    Buffer response = sendHttpPostRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, REGISTER_PATH, &dataToSend, NULL, CONNECTION_TIMEOUT_MS);

    if(response.data == NULL)
        return 3;
        
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(dataToSend.data);
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == 0)
    {
        cJSON *auth_token_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "auth_token");
        if(auth_token_obj == NULL)
            return 2;
        char *auth_token_str = auth_token_obj->valuestring;
        auth_token = getStringCopy(auth_token_str);
        cJSON_free(auth_token_obj);
    }

    free(dataToSend.data);
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);

    return ret_code; //can display a message saying what hapenned and return acordingly
}

/*
* Creates logout request, sends it to the web server and returns true if aproved, false otherwise.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 1 - auth_token NULL, you must be logged in to call this method
* 2 - server error.
* 3 - can't connect to server.
* Logout request is type POST to /logout
*/
int logoutRequest()
{
    if(auth_token == NULL)
        return 1;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();
    Buffer response = sendHttpPostRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, LOGOUT_PATH, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    if(response.data == NULL)
        return 3;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    free(auth_token);

    auth_token = NULL; //reset auth_token
    return ret_code; //can display a message saying what hapenned and return acordingly
}


/**
* Sends a request to list all exercises. Returns a list of all exercises received from the web server. Returns an int code indentifying the result of the request.
* @param exercises_list The exercises list received from server. A pointer to a (char size_t variable type (previously allocated)) should be passed as parameter.
* @param number_of_exercises The number of exercises received from server (returns by reference). A pointer to a size_t variable type (previously allocated) should be passed.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - server error.
* 3 - can't connect to server.
*/
int getExercisesListRequest(ExerciseSimplified *exercises_list[], size_t *number_of_exercises)
{
    char *additionalHeaderString = NULL;
    if(auth_token != NULL)
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    Buffer response = sendHttpGetRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, GET_EXERCISES_PATH, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    if(response.data == NULL)
        return 3;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == 0)
    {
        cJSON *exercises = cJSON_GetObjectItemCaseSensitive(monitor_json, "exercises");
        if(exercises == NULL)
            return 2;
        cJSON *exercise;
        *number_of_exercises = cJSON_GetArraySize(exercises);
        *exercises_list = malloc(sizeof(ExerciseSimplified) *  (*number_of_exercises));
        size_t i = 0;

        cJSON_ArrayForEach(exercise, exercises)
        {
            cJSON *id_obj = cJSON_GetObjectItemCaseSensitive(exercise, "id");
            if(id_obj == NULL)
                return 2;
            cJSON *title_obj = cJSON_GetObjectItemCaseSensitive(exercise, "title");
            if(title_obj == NULL)
                return 2;
            cJSON *progress_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "progress"); //progress can be NULL in case user not logged in
            if (!cJSON_IsString(id_obj))            
            {
                free(response.data);
                cJSON_free(monitor_json);
                cJSON_free(ret_code_obj);
                free(*exercises_list);
                cJSON_free(exercises);
                cJSON_free(exercise);
                cJSON_free(id_obj);
                cJSON_free(title_obj);
                cJSON_free(progress_obj);
                return 2;
            }
            int id = atoi(id_obj->valuestring);
            if (id == 0)
            {
                free(response.data);
                cJSON_free(monitor_json);
                cJSON_free(ret_code_obj);
                free(*exercises_list);
                cJSON_free(exercises);
                cJSON_free(exercise);
                cJSON_free(id_obj);
                cJSON_free(title_obj);
                return 2;
            }
            char *title_str = title_obj->valuestring;
            (*exercises_list)[i].id = id;
            (*exercises_list)[i].title = getStringCopy(title_str);
            if(progress_obj == NULL || progress_obj->valuestring == NULL)
            {
                (*exercises_list)[i].progress = 0;
            }
            else
            {
                int progress = atoi(progress_obj->valuestring);
                (*exercises_list)[i].progress = progress;
            }
    
            cJSON_free(id_obj);
            cJSON_free(title_obj);
            cJSON_free(progress_obj);

             i++;
        }
        
        cJSON_free(exercises);
        cJSON_free(exercise);
        
    }
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    return ret_code; //can display a message saying what hapenned and return acordingly
}

/**
* Creates an exercise struct based on the received exercise from the web server. Returns an int code indentifying the result of the request.
* @param exercise_id The id of the exercise to load from server.
* @param exercise The exercise received from server (returns by reference). A pointer to a (tic_exercise struct (previously allocated)) should be passed as parameter.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 1 - access denied.
* 2 - server error.
* 3 - can't connect to server.
*/
int getExerciseDetailsRequest(int exercise_id, tic_exercise *exercise)
{   
    char *additionalHeaderString = NULL;
    if(auth_token != NULL) //if logged in, the web server will receive the auth token in order to check if user can receive that exercise data.
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    char *request_address = malloc(sizeof(char) * (strlen(GET_EXERCISE_DETAILS_PATH) + 1 + (log10(exercise_id) + 1)));
    sprintf(request_address, "%s/%d", GET_EXERCISE_DETAILS_PATH, exercise_id);
    Buffer response = sendHttpGetRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, request_address, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    free(request_address);
    if(response.data == NULL)
        return 3;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(response.data);
        free(error_ptr);
        cJSON_free(monitor_json);
        return 2;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == 0)
    {
        exercise->id = exercise_id;
        cJSON *exercise_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "exercise");
        if(exercise_obj == NULL)
            return 2;
          
        
        cJSON *exercise_element;
        cJSON_ArrayForEach(exercise_element, exercise_obj)
        {
            cJSON *title_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "title");
            if(title_obj == NULL || title_obj->valuestring == NULL)
                return 2;
            exercise->title = getStringCopy(title_obj->valuestring);

            cJSON *creator_name_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "creator_name");
            if(creator_name_obj == NULL)
                return 2;
            exercise->creator_name = getStringCopy(creator_name_obj->valuestring);

            cJSON *description_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "description");
            if(description_obj == NULL)
                return 2;
            exercise->description = getStringCopy(description_obj->valuestring);

            cJSON *img_base64_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "image_base64");
            if(img_base64_obj == NULL)
                return 2;
            exercise->img_base64 = getStringCopy(img_base64_obj->valuestring);

            cJSON *progress_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "progress");
            if(progress_obj == NULL || progress_obj->valuestring == NULL)
                exercise->progress = 0;
            else
                exercise->progress = atoi(progress_obj->valuestring);

            if(parseExerciseTestsReceived(monitor_json, exercise) == 2)
                return 2;
        
            cJSON_free(title_obj);
            cJSON_free(creator_name_obj);
            cJSON_free(description_obj);
            cJSON_free(img_base64_obj);
            cJSON_free(progress_obj);
            cJSON_free(exercise_obj);
        
        }

    }
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);

    return ret_code; //can display a message saying what hapenned and return acordingly
}

/**
* Parses the exercises tests that come in JSON and puts them in the exerciseTestArray of ExerciseTest struct. Returns an int code identifying the result of the parse.
* @param exercise_element A cJSON element representing the exercise tests info related.
* @param exerciseTestArray A ExerciseTest instance for putting the exercise tests info. Double pointer to be allocated inside, when the number of tests is known.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - parsing error.
*/
int parseExerciseTestsReceived(cJSON *exercise_element, tic_exercise *ticExercise)
{
    int ret_code = 0;
    ExerciseTest **exerciseTestArray = &(ticExercise->exerciseTest);
    cJSON *tests_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "tests");
    if(tests_obj == NULL)
    {
        cJSON_free(tests_obj);
        return 2;
    }
    ticExercise->number_of_exercise_tests = cJSON_GetArraySize(tests_obj);
    *exerciseTestArray = malloc(sizeof(ExerciseTest) * ticExercise->number_of_exercise_tests);

    cJSON *test;
    size_t i = 0;
    cJSON_ArrayForEach(test, tests_obj)
    {
        cJSON *id_obj = cJSON_GetObjectItemCaseSensitive(test, "id");
        cJSON *title_obj = cJSON_GetObjectItemCaseSensitive(test, "title");
        cJSON *hint_obj = cJSON_GetObjectItemCaseSensitive(test, "hint");
        cJSON *test_code_obj = cJSON_GetObjectItemCaseSensitive(test, "test_code");

        if(id_obj == NULL || id_obj->valuestring == NULL)
        {
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        int id = atoi(id_obj->valuestring);
        if(id == 0)
        {
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].id = id;
        
        if(title_obj == NULL || title_obj->valuestring == NULL)
        {
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].title = title_obj->valuestring;
        
        if(hint_obj == NULL|| hint_obj->valuestring == NULL)
        {
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].hint = hint_obj->valuestring;

        if(test_code_obj == NULL|| test_code_obj->valuestring == NULL)
        {
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        size_t code_decoded_size = b64_decoded_size(test_code_obj->valuestring);
	    char *code_decoded = malloc(sizeof(char) * code_decoded_size);
	    if (b64_decode(test_code_obj->valuestring, code_decoded, code_decoded_size) != 1)
		{
            free(code_decoded);
            ret_code = 2;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].test_code = code_decoded;

deallocate_parseExerciseTestsReceived:
        cJSON_free(id_obj);
        cJSON_free(title_obj);
        cJSON_free(hint_obj);
        cJSON_free(test_code_obj);

        if (ret_code == 2)
            goto deallocate_parseExerciseTestsReceivedAndReturn;
        i++;
    }

deallocate_parseExerciseTestsReceivedAndReturn:
    cJSON_free(tests_obj);
    cJSON_free(test);
 
    return ret_code;
}

/**
* Creates save exercise progress request and sends it to the web server. Returns an int code identifying the result of the request.
* @param exercise_data The data of the exercise to save (binary data).
* @param progress An int representing the current progress on the exercise.
* @param exercise_id An int representing the id of the exercise of which to save the progress.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 1 - must be logged in to save progress.
* 2 - server error.
* 3 - can't connect to server.
*/
int saveProgressRequest(Buffer exercise_data, char *code, int exercise_id)
{
    if(auth_token == NULL)
        return 1;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();
        
    Buffer dataToSend;
    int FIXED_SAVE_PROGRESS_MESSAGE_SIZE = 20;
    char *exercise_data_encoded = b64_encode(exercise_data.data, exercise_data.size);
    char *code_encoded = b64_encode(code, strlen(code) * sizeof(char));
    dataToSend.size = strlen(exercise_data_encoded) + strlen(code_encoded) + FIXED_SAVE_PROGRESS_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "exercise_data=%s&code=%s", exercise_data_encoded, code_encoded);
    
    char *request_address = malloc(sizeof(char) * (strlen(SAVE_PROGRESS_PATH) + 1 + log10(exercise_id) + 1 + 4));
    sprintf(request_address, "%s/%d/save", SAVE_PROGRESS_PATH, exercise_id);

    Buffer response = sendHttpPostRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, request_address, &dataToSend, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    if(response.data == NULL)
        return 3;
    
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(dataToSend.data);
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return 2;
    int ret_code = ret_code_obj->valueint;
    free(dataToSend.data);
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    return ret_code;
}


/**
* Creates test code on server request and sends it to the web server. Returns an int code identifying the result of the request.
* @param exercise_id An int representing the id of the exercise of which student code tries to resolve.
* @param code A string with student typed code to be tested.
* @param ticExercise The struct representing the exercise that will be filled with the result from the tests.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - server error.
* 3 - can't connect to server.
*/
int sendCodeToServerAndGetTestsResults(int exerciseId, char *code, tic_exercise *ticExercise)
{
    char *additionalHeaderString = NULL;
    if(auth_token != NULL) //if logged in, the web server will receive the auth token in order to sava the most recent progress of the user based on the code tested.
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    int ret_code;
    Buffer dataToSend;
    int FIXED_EXECUTE_TEST_MESSAGE_SIZE = 5;
    dataToSend.size = strlen(code) + FIXED_EXECUTE_TEST_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "code=%s", code);
    char *request_address = malloc(sizeof(char) * (strlen(EXECUTE_TEST_PATH) + 1 + (log10(exerciseId) + 1) + 1 + 4));
    sprintf(request_address, "%s/%d/test", EXECUTE_TEST_PATH, exerciseId);

    Buffer response = sendHttpGetRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, request_address, &dataToSend, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    if(response.data == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return 3;
    }
    printf("\n\nresponse.data: %s\n\n", response.data);
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        free(dataToSend.data);
        free(response.data);
        cJSON_free(monitor_json);
        return 2;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
    {
        ret_code = 2;
        goto deallocate_memory;
    }
    ret_code = ret_code_obj->valueint;
    if(ret_code == 0)
    {
        cJSON *tests_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "tests_results");
        if(tests_obj == NULL)
        {
            cJSON_free(tests_obj);
            ret_code = 2;
            goto deallocate_memory;
        }

        cJSON *test;
        cJSON_ArrayForEach(test, tests_obj)
        {
            cJSON *id_obj = cJSON_GetObjectItemCaseSensitive(test, "id");
            cJSON *result_obj = cJSON_GetObjectItemCaseSensitive(test, "result");

            if(id_obj == NULL || id_obj->valuestring == NULL)
                return 2;
            int id = atoi(id_obj->valuestring);
            cJSON_free(id_obj);
            if(id == 0)
            {
                cJSON_free(tests_obj);
                cJSON_free(test);
                ret_code = 2;
                goto deallocate_memory;
            }

            if(result_obj == NULL || result_obj->valuestring == NULL)
            {
                cJSON_free(result_obj);
                cJSON_free(tests_obj);
                cJSON_free(test);
                ret_code = 2;
                goto deallocate_memory;
            }
printDebugMsg();
            bool passed = strcmp(result_obj->valuestring, "OK") == 0 ? true : false;
            ExerciseTest *exerciseTestArray = ticExercise->exerciseTest;
            for(size_t i = 0; i < ticExercise->number_of_exercise_tests; i++)
            {
                if(exerciseTestArray[i].id == id)
                    exerciseTestArray[i].passed = passed;
            }
            cJSON_free(result_obj);
printDebugMsg();;
        }

        cJSON_free(tests_obj);
        cJSON_free(test);
    }

deallocate_memory:
    free(dataToSend.data);
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    
    return ret_code;
}
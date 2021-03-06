#include "web_comunication_api.h"
#include "base64_enc_dec.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/**
* Global variable that contains the token of the session. Is filled when login, and destroyed in logout.
*/
char *auth_token = NULL;

/**
* Global variable for the file that contains the server address. Is filled when application starts with config in file with path CONFIGS_FILE_PATH.
*/
char *server_address = NULL;

/**
* Global variable for the file that contains the server port. Is filled when application starts with config in file with path CONFIGS_FILE_PATH.
*/
int server_port;

/**
* Loads the config file with server port and server address.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* -1 - file not exists.
* -2 - error parsing file.
*/
int loadServerConfigsFromFile(char *conf_file_path)
{
    FILE *file;
    file = fopen(conf_file_path, "r");
    if (!file)
        return -2; 

    int size_server_address = 0;
    if((size_server_address = getline(&server_address, &size_server_address, file)) == EOF)
    {
        free(server_address);
        return -1;
    }
    setNullTerminatorAtFirstCarriageReturnOrLineFeed(server_address);
    getStringAfterEqualSymbol(&server_address);
        
    char *server_port_string = NULL;
    int size_server_port = 0;
    if(getline(&server_port_string, &size_server_port, file) == EOF)
    {
        free(server_port_string);
        return -1;
    }
    getStringAfterEqualSymbol(&server_port_string);
    server_port = strtol(server_port_string, (char **)NULL, 10);

    fclose(file);
    return 0;
}

/**
* Changes the pointer to the data after '=' character, in order to get only the data, placed after the double '='.
* @param buf The char pointer that contains the data received, of which the pointer will be changed.
*/
void getStringAfterEqualSymbol(char **string)
{
	char *ocurrence = strstr(*string, "=");
	ocurrence += sizeof(char) * strlen("=");
	size_t new_size = sizeof(char) * (strlen(ocurrence) + 1);
	char *new_data = malloc(new_size);
	memcpy(new_data, ocurrence, new_size);
	new_data[new_size - 1] = '\0';
	free(*string);
	*string = new_data;
}

/**
* Changes the string value by setting the null terminator ate the first '\r' or '\n' character.
* @param buf The char pointer that contains the string received, of which null terminator will be set.
*/
void setNullTerminatorAtFirstCarriageReturnOrLineFeed(char *string)
{
    for(int i = 0;; i++)
    {
        if(string[i] == '\r' || string[i] == '\n')
        {
            string[i] = '\0';
            return;
        }
    }
}

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
    return loginRequestSend(username, password, false, NULL);
}


int loginRequestSend(const char *username, const char *password, bool testing, char *mock_response_data)
{
    Buffer dataToSend;
    int FIXED_LOGIN_MESSAGE_SIZE = 19;
    dataToSend.size = strlen(username) + strlen(password) + FIXED_LOGIN_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "username=%s&password=%s", username, password);
    Buffer response;
    if (!testing)
        response = sendHttpPostRequest(server_address, server_port, LOGIN_PATH, &dataToSend, NULL, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        memcpy(mock_response_data, dataToSend.data, strlen(dataToSend.data) + 1);
    }
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
    
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return SERVER_ERROR;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == SUCCESS)
    {
        cJSON *auth_token_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "auth_token");
        if(auth_token_obj == NULL)
            return SERVER_ERROR;
        char *auth_token_str = auth_token_obj->valuestring;
        if(auth_token_str == NULL)
            return SERVER_ERROR;
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
    return registerRequestSend(name, email, username, password, false, NULL);
}


int registerRequestSend(const char *name, const char *email, const char *username, const char *password, bool testing, char *mock_response_data)
{
    Buffer dataToSend;
    int FIXED_REGISTER_MESSAGE_SIZE = 32;
    dataToSend.size = strlen(name) + strlen(email) + strlen(username) + strlen(password) + FIXED_REGISTER_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "name=%s&email=%s&username=%s&password=%s",
            name, email, username, password);
    Buffer response;
    if (!testing)
        response = sendHttpPostRequest(server_address, server_port, REGISTER_PATH, &dataToSend, NULL, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        memcpy(mock_response_data, dataToSend.data, strlen(dataToSend.data) + 1);
    }
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
        
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return SERVER_ERROR;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == SUCCESS)
    {
        cJSON *auth_token_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "auth_token");
        if(auth_token_obj == NULL)
            return SERVER_ERROR;
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
    return logoutRequestSend(false, NULL);
}

int logoutRequestSend(bool testing, char *mock_response_data)
{
    if(auth_token == NULL)
        return FORBIDDEN;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();
    Buffer response;
    if (!testing)
        response = sendHttpPostRequest(server_address, server_port, LOGOUT_PATH, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        memcpy(mock_response_data, additionalHeaderString, strlen(additionalHeaderString) + 1);
    }
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(response.data);
        return SERVER_ERROR;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
    int ret_code = ret_code_obj->valueint;
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    
    if (ret_code == SUCCESS)
    {
        //reset auth_token
        free(auth_token);
        auth_token = NULL;
    }

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
    return getExercisesListRequestSend(exercises_list, number_of_exercises, false, NULL);
}


int getExercisesListRequestSend(ExerciseSimplified *exercises_list[], size_t *number_of_exercises, bool testing, char *mock_response_data)
{
    char *additionalHeaderString = NULL;
    if(auth_token != NULL)
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    Buffer response;
    if (!testing)
        response = sendHttpGetRequest(server_address, server_port, GET_EXERCISES_PATH, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        memcpy(mock_response_data, additionalHeaderString, strlen(additionalHeaderString) + 1);
    }
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(response.data);
        return SERVER_ERROR;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == SUCCESS)
    {
        cJSON *exercises = cJSON_GetObjectItemCaseSensitive(monitor_json, "exercises");
        if(exercises == NULL)
            return SERVER_ERROR;
        cJSON *exercise;
        *number_of_exercises = cJSON_GetArraySize(exercises);
        *exercises_list = malloc(sizeof(ExerciseSimplified) *  (*number_of_exercises));
        size_t i = 0;

        cJSON_ArrayForEach(exercise, exercises)
        {
            cJSON *id_obj = cJSON_GetObjectItemCaseSensitive(exercise, "id");
            if(id_obj == NULL)
                return SERVER_ERROR;
            cJSON *title_obj = cJSON_GetObjectItemCaseSensitive(exercise, "title");
            if(title_obj == NULL)
                return SERVER_ERROR;
            cJSON *progress_obj = cJSON_GetObjectItemCaseSensitive(exercise, "progress"); //progress can be NULL in case user not logged in
            int id = id_obj->valueint;
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
                return SERVER_ERROR;
            }
            char *title_str = title_obj->valuestring;
            (*exercises_list)[i].id = id;
            (*exercises_list)[i].title = getStringCopy(title_str);
            if(progress_obj == NULL)
            {
                (*exercises_list)[i].progress = 0;
            }
            else
            {
                int progress = progress_obj->valueint;
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
    return getExerciseDetailsRequestSend(exercise_id, exercise, false, NULL);
}

int getExerciseDetailsRequestSend(int exercise_id, tic_exercise *exercise, bool testing, char *mock_response_data)
{   
    char *additionalHeaderString = NULL;
    if(auth_token != NULL) //if logged in, the web server will receive the auth token in order to check if user can receive that exercise data.
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    char *request_address = malloc(sizeof(char) * (strlen(GET_EXERCISE_DETAILS_PATH) + 1 + (log10(exercise_id) + 1)));
    sprintf(request_address, "%s/%d", GET_EXERCISE_DETAILS_PATH, exercise_id);
    Buffer response;
    if (!testing)
        response = sendHttpGetRequest(server_address, server_port, request_address, NULL, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        memcpy(mock_response_data, additionalHeaderString, strlen(additionalHeaderString) + 1);
    }
    
    free(request_address);
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(response.data);
        return SERVER_ERROR;
    }
    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
    int ret_code = ret_code_obj->valueint;
    if (ret_code == SUCCESS)
    {
        exercise->id = exercise_id;
        cJSON *exercise_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "exercise");
        if(exercise_obj == NULL)
            return SERVER_ERROR;
          
        
        cJSON *exercise_element;
        cJSON_ArrayForEach(exercise_element, exercise_obj)
        {
            cJSON *title_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "title");
            if(title_obj == NULL || title_obj->valuestring == NULL)
                return SERVER_ERROR;
            exercise->title = getStringCopy(title_obj->valuestring);

            cJSON *creator_name_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "creator_name");
            if(creator_name_obj == NULL)
                return SERVER_ERROR;
            exercise->creator_name = getStringCopy(creator_name_obj->valuestring);

            cJSON *description_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "description");
            if(description_obj == NULL)
                return SERVER_ERROR;
            exercise->description = getStringCopy(description_obj->valuestring);
            
            cJSON *feup8_file_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "feup8_file");
            if(feup8_file_obj == NULL)
                return SERVER_ERROR;
        
            size_t decode_size = 0;
            if(strlen(feup8_file_obj->valuestring) != 0)
            {
                decode_size = hexs2bin(feup8_file_obj->valuestring, &exercise->feup8_file.data);
                if(decode_size == -1)
                {
                    free(exercise->feup8_file.data);
                    return SERVER_ERROR;
                }
            }
          
            exercise->feup8_file.size = decode_size;
            cJSON *progress_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "progress");
            if(progress_obj == NULL)
                exercise->progress = 0;
            else
                exercise->progress = progress_obj->valueint;

            if (parseExerciseTestsReceived(monitor_json, exercise) == 2)
                return SERVER_ERROR;

            cJSON_free(title_obj);
            cJSON_free(creator_name_obj);
            cJSON_free(description_obj);
            cJSON_free(progress_obj);
            cJSON_free(exercise_obj);    
        }
    }
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);

    int NOT_EVALUATED_YET = -2;
    setAllTestsAsValue(exercise, NOT_EVALUATED_YET); //set tests passes value as not filled yet (in this case -2)
    exercise->tests_global_state = (NOT_EVALUATED_YET - 1); //set global state as not evaluated yet (in this case -3)

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
    int ret_code = SUCCESS;
    ExerciseTest **exerciseTestArray = &(ticExercise->exerciseTests);
    cJSON *tests_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "tests");
    if(tests_obj == NULL)
        return SERVER_ERROR;
    
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

        if(id_obj == NULL)
        {
            ret_code = SERVER_ERROR;
            goto deallocate_parseExerciseTestsReceived;
        }
        int id = id_obj->valueint;
        if(id == 0)
        {
            ret_code = SERVER_ERROR;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].id = id;
        
        if(title_obj == NULL || title_obj->valuestring == NULL)
        {
            ret_code = SERVER_ERROR;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].title = title_obj->valuestring;
        
        if(hint_obj == NULL || hint_obj->valuestring == NULL)
           (*exerciseTestArray)[i].hint = "";
        else
            (*exerciseTestArray)[i].hint = hint_obj->valuestring;

        if(test_code_obj == NULL || test_code_obj->valuestring == NULL)
        {
            ret_code = SERVER_ERROR;
            goto deallocate_parseExerciseTestsReceived;
        }
        size_t code_decoded_size = b64_decoded_size(test_code_obj->valuestring);
	    char *code_decoded = calloc(code_decoded_size, sizeof(char));
	    if (b64_decode(test_code_obj->valuestring, code_decoded, code_decoded_size) != 1)
		{
            free(code_decoded);
            ret_code = SERVER_ERROR;
            goto deallocate_parseExerciseTestsReceived;
        }
        (*exerciseTestArray)[i].test_code = code_decoded;

deallocate_parseExerciseTestsReceived:
        cJSON_free(id_obj);
        cJSON_free(title_obj);
        cJSON_free(hint_obj);
        cJSON_free(test_code_obj);

        if (ret_code == SERVER_ERROR)
            goto deallocate_parseExerciseTestsReceivedAndReturn;
        i++;
    }

deallocate_parseExerciseTestsReceivedAndReturn:
    cJSON_free(tests_obj);
 
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
    return saveProgressRequestSend(exercise_data, code, exercise_id, false, NULL);
}

int saveProgressRequestSend(Buffer exercise_data, char *code, int exercise_id, bool testing, char *mock_response_data)
{
    if(auth_token == NULL)
        return FORBIDDEN;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();
        
    Buffer dataToSend;
    int FIXED_SAVE_PROGRESS_MESSAGE_SIZE = 20;
    char *exercise_data_encoded = bin2hex(exercise_data.data, exercise_data.size);
    char *code_encoded = b64_encode(code, strlen(code) * sizeof(char));
    dataToSend.size = strlen(exercise_data_encoded) + strlen(code_encoded) + FIXED_SAVE_PROGRESS_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "exercise_data=%s&code=%s", exercise_data_encoded, code_encoded);
    char *request_address = malloc(sizeof(char) * (strlen(SAVE_PROGRESS_PATH) + 1 + log10(exercise_id) + 1 + 4));
    sprintf(request_address, "%s/%d/save", SAVE_PROGRESS_PATH, exercise_id);

    Buffer response;
    if (!testing)
        response = sendHttpPostRequest(server_address, server_port, request_address, &dataToSend, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        char *data_sent_to_server = concateStrings(additionalHeaderString, "\n\n");
        data_sent_to_server = concateStrings(data_sent_to_server, dataToSend.data);
        memcpy(mock_response_data, data_sent_to_server, strlen(data_sent_to_server) + 1);
    }
    if(response.data == NULL)
        return CANT_CONNECT_TO_SERVER;
    
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return SERVER_ERROR;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
        return SERVER_ERROR;
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
*  0 - success.
*  2 - server error.
*  3 - can't connect to server.
* -2 - timeout on running tests on server
* -1 - syntactic errors on running tests on server
*/
int sendCodeToServerAndGetTestsResults(int exerciseId, char *code, tic_exercise *ticExercise)
{
    
    return sendCodeToServerAndGetTestsResultsRequestSend(exerciseId, code, ticExercise, false, NULL);
}

int sendCodeToServerAndGetTestsResultsRequestSend(int exerciseId, char *code, tic_exercise *ticExercise, bool testing, char *mock_response_data)
{
	//assert that only is tested code that has at least one test
    if(ticExercise->number_of_exercise_tests <= 0)
        return INVALID_ARGUMENTS;

    char *additionalHeaderString = NULL;
    if(auth_token != NULL) //if logged in, the web server will receive the auth token in order to sava the most recent progress of the user based on the code tested.
        additionalHeaderString = getAdditionalHeaderStringWithAuthToken();

    int ret_code;
    Buffer dataToSend;
    int FIXED_EXECUTE_TEST_MESSAGE_SIZE = 5;
    char *code_encoded = b64_encode(code, strlen(code) * sizeof(char));
    dataToSend.size = strlen(code_encoded) + FIXED_EXECUTE_TEST_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * (dataToSend.size + 1));
    sprintf(dataToSend.data, "code=%s", code_encoded);
    char *request_address = malloc(sizeof(char) * (strlen(EXECUTE_TEST_PATH) + 1 + (log10(exerciseId) + 1) + 1 + 4));
    sprintf(request_address, "%s/%d/test", EXECUTE_TEST_PATH, exerciseId);

    Buffer response;
    if (!testing)
        response = sendHttpGetRequest(server_address, server_port, request_address, &dataToSend, additionalHeaderString, CONNECTION_TIMEOUT_MS);
    else
    {
        response.data = getStringCopy(mock_response_data);
        response.size = strlen(mock_response_data);
        char *data_sent_to_server = concateStrings(additionalHeaderString, "\n\n");
        data_sent_to_server = concateStrings(data_sent_to_server, dataToSend.data);
        memcpy(mock_response_data, data_sent_to_server, strlen(data_sent_to_server) + 1);
    }
    
    if(response.data == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return CANT_CONNECT_TO_SERVER;
    }
    
    cJSON *monitor_json = cJSON_Parse(response.data);
    if (monitor_json == NULL)
    {
        free(dataToSend.data);
        free(response.data);
        return SERVER_ERROR;
    }

    cJSON *ret_code_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "response_code");
    if(ret_code_obj == NULL)
    {
        ret_code = SERVER_ERROR;
        goto deallocate_memory;
    }

    ret_code = ret_code_obj->valueint;
    if(ret_code == SUCCESS)
    {
        cJSON *tests_global_state_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "tests_global_state");
        if(tests_global_state_obj == NULL)
        {
            cJSON_free(tests_global_state_obj);
            ret_code = SERVER_ERROR;
            goto deallocate_memory;
        }
        setAllTestsAsValue(ticExercise, 0); //set as not passed
        ticExercise->tests_global_state = tests_global_state_obj->valueint;
        if(ticExercise->tests_global_state == EXECUTION_TIMEOUT)
            return EXECUTION_TIMEOUT;
        if(ticExercise->tests_global_state == SYNTACTIC_ERRORS)
            return SYNTACTIC_ERRORS;

        cJSON *tests_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "tests_results");
        if(tests_obj == NULL)
        {
            cJSON_free(tests_global_state_obj);
            cJSON_free(tests_obj);
            ret_code = SERVER_ERROR;
            goto deallocate_memory;
        }

        ExerciseTest *exerciseTestArray = ticExercise->exerciseTests;
        for(size_t i = 0; i < ticExercise->number_of_exercise_tests; i++)
        {
            char *test_title = exerciseTestArray[i].title;
            cJSON *result_obj = cJSON_GetObjectItemCaseSensitive(tests_obj, test_title);

            if(result_obj == NULL)
            {
                cJSON_free(tests_global_state_obj);
                cJSON_free(tests_obj);
                cJSON_free(result_obj);
                ret_code = SERVER_ERROR;
                goto deallocate_memory;
            }
            int passed = cJSON_IsTrue(result_obj) == true ? 1 : 0;
            exerciseTestArray[i].passed = passed;
        }
       
        cJSON_free(tests_global_state_obj);
        cJSON_free(tests_obj);
    }

deallocate_memory:
    free(dataToSend.data);
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);
    
    return ret_code;
}

/**
* Sets all the exercises tests passed value as the value passed as paramater
* @param ticExercise The struct representing the exercise that will be filled with the result from the tests.
* @param value the value to set in exercise tests 
*/
void setAllTestsAsValue(tic_exercise *ticExercise, int value)
{
    ExerciseTest *exerciseTests = ticExercise->exerciseTests;
    for(size_t i = 0; i < ticExercise->number_of_exercise_tests; i++)
    {
        exerciseTests[i].passed = value;
    }
}
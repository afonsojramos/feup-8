#include "web_comunication_api.h"
#include "net.h"
#include "base64_enc_dec.h"
#include "cJSON.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    dataToSend.data = malloc(sizeof(u8) * dataToSend.size);
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
* @param username The username to register with.
* @param password The password to register with.
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
    dataToSend.data = malloc(sizeof(u8) * dataToSend.size);
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
    //auth_token = NULL; //reset auth_token
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

    return ret_code; //can display a message saying what hapenned and return acordingly
}


/**
* Creates a list of all exercises received from the web server . Returns an int code indentifying the result of the request.
* @param exercises_list The exercises list received from server. A pointer to a (char pointer (previously allocated)) should be passed as parameter.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - server error.
* 3 - can't connect to server.
*/
int getExercisesListRequest(ExerciseSimplified *exercises_list[], size_t *number_of_exercises)
{
    //TODO: tirar auth_token
    /*if(auth_token == NULL)
        return 1;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();*/

    Buffer response = sendHttpGetRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, GET_EXERCISES_PATH, NULL, NULL, CONNECTION_TIMEOUT_MS);
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
* @param exercise The exercise received from server. A double pointer to a Exercise should be passed as parameter, in order to allocate memory for it inside.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 2 - server error.
* 3 - can't connect to server.
*/
int getExerciseDetailsRequest(int exercise_id, tic_exercise *exercise)
{   
    //TODO: tirar auth_token
  /*  if(auth_token == NULL)
        return NULL;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();*/
    char *request_address = malloc(sizeof(char) * (strlen(GET_EXERCISE_DETAILS_PATH) + log10(exercise_id) + 1 + 1));
    sprintf(request_address, "%s/%d", GET_EXERCISE_DETAILS_PATH, exercise_id);
    Buffer response = sendHttpGetRequest(WEB_SERVER_ADDRESS, WEB_SERVER_PORT, request_address, NULL, NULL, CONNECTION_TIMEOUT_MS);
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
        exercise->id = exercise_id;
       cJSON *exercise_obj = cJSON_GetObjectItemCaseSensitive(monitor_json, "exercise");
        if(exercise_obj == NULL)
            return 2;
          
        
        cJSON *exercise_element;
        size_t i = 0;

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

            cJSON *correct_code_base64_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "correct_code_base64");
            if(correct_code_base64_obj == NULL)
                return 2;
            exercise->exerciseTest.correct_code_base64 = getStringCopy(correct_code_base64_obj->valuestring);

            cJSON *test_code_base64_obj = cJSON_GetObjectItemCaseSensitive(exercise_element, "test_code_base64");
            if(test_code_base64_obj == NULL)
                return 2;
            exercise->exerciseTest.test_code_base64 = getStringCopy(test_code_base64_obj->valuestring);

                    
            cJSON_free(correct_code_base64_obj);
            cJSON_free(test_code_base64_obj);
            cJSON_free(title_obj);
            cJSON_free(creator_name_obj);
            cJSON_free(description_obj);
            cJSON_free(img_base64_obj);
            cJSON_free(progress_obj);

            i++;
        }

    }
    free(response.data);
    cJSON_free(monitor_json);
    cJSON_free(ret_code_obj);

    return ret_code; //can display a message saying what hapenned and return acordingly
}

/**
* Creates save exercise progress request and sends it to the web server. Returns an int code indentifying the result of the request.
* @param exercise_data The data of the exercise to save (binary data).
* @param progress An int representing the current progress on the exercise.
* @param exercise_id An int representing the id of the exercise of which to save the progress.
* @return An int identifying the result of the request. Int returned and respective meaning:
* 0 - success.
* 1 - must be logged in to save progress.
* 2 - server error.
* 3 - can't connect to server.
*/
int saveProgressRequest(Buffer exercise_data, int progress, int exercise_id)
{
    if(auth_token == NULL)
        return 1;
    char *additionalHeaderString = getAdditionalHeaderStringWithAuthToken();
        
    Buffer dataToSend;
    int FIXED_SAVE_PROGRESS_MESSAGE_SIZE = 24;
    char *exercise_data_encoded = b64_encode(exercise_data.data, exercise_data.size);
    dataToSend.size = strlen(exercise_data_encoded) + log10(progress) + 1 + FIXED_SAVE_PROGRESS_MESSAGE_SIZE;
    dataToSend.data = malloc(sizeof(u8) * dataToSend.size);
    sprintf(dataToSend.data, "exercise_data=%s&progress=%d", exercise_data.data, progress);
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
#ifndef web_comunication_api__h
#define web_comunication_api__h

#include "ticapi.h"
#include "cJSON.h"
#include "net.h"
#include <string.h>

#define CONFIGS_FILE_PATH "conf.ini"
#define REGISTER_PATH "/api/register"
#define LOGIN_PATH "/api/login"
#define LOGOUT_PATH "/api/logout"
#define GET_EXERCISES_PATH "/api/exercises/all"
#define GET_EXERCISE_DETAILS_PATH "/api/exercises"
#define SAVE_PROGRESS_PATH "/api/exercises"
#define EXECUTE_TEST_PATH "/api/exercises"
#define CONNECTION_TIMEOUT_MS 2000


//Return codes
#define SUCCESS 0
#define WRONG_CREDENTIALS 1
#define FORBIDDEN 1
#define SERVER_ERROR 2
#define CANT_CONNECT_TO_SERVER 3

//Tests codes
#define EXECUTION_TIMEOUT -2
#define SYNTACTIC_ERRORS -1
#define CODE_APPROVED 0

typedef struct 
{
		int id;
    char *title;
    int progress; //-1 if not logged in
} ExerciseSimplified;

int loadServerConfigsFromFile(char *conf_file_path);
void getStringAfterEqualSymbol(char **string);
void setNullTerminatorAtFirstCarriageReturnOrLineFeed(char *string);
char *getAdditionalHeaderStringWithAuthToken();
static char* getStringCopy(const char *original);
int loginRequest(const char *username, const char *password);
int loginRequestSend(const char *username, const char *password, bool testing, char *mock_response_data);
int logoutRequest();
int logoutRequestSend(bool testing, char *mock_response_data);
int registerRequest(const char *name, const char *email, const char *username, const char *password);
int registerRequestSend(const char *name, const char *email, const char *username, const char *password, bool testing, char *mock_response_data);
int getExercisesListRequest(ExerciseSimplified *exercises_list[], size_t *number_of_exercises);
int getExercisesListRequestSend(ExerciseSimplified *exercises_list[], size_t *numberOfExercises, bool testing, char *mock_response_data);
int getExerciseDetailsRequest(int exercise_id, tic_exercise *exercise);
int getExerciseDetailsRequestSend(int exercise_id, tic_exercise *exercise, bool testing, char *mock_response_data);
int parseExerciseTestsReceived(cJSON *exercise_element, tic_exercise *ticExercise);
int saveProgressRequest(Buffer exercise_data, char *code, int exercise_id);
int saveProgressRequestSend(Buffer exercise_data, char *code, int exercise_id, bool testing, char *mock_response_data);
int sendCodeToServerAndGetTestsResults(int exerciseId, char *code, tic_exercise *ticExercise);
int sendCodeToServerAndGetTestsResultsRequestSend(int exerciseId, char *code, tic_exercise *ticExercise, bool testing, char *mock_response_data);
void setAllTestsAsValue(tic_exercise *ticExercise, int value);


#endif
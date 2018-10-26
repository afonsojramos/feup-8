#ifndef web_comunication_api__h
#define web_comunication_api__h

#include "ticapi.h"
#include "cJSON.h"
#include "net.h"
#include <string.h>

#define WEB_SERVER_ADDRESS "127.0.0.1"
#define WEB_SERVER_PORT 8000
#define REGISTER_PATH "/api/register"
#define LOGIN_PATH "/api/login"
#define LOGOUT_PATH "/api/logout"
#define GET_EXERCISES_PATH "/api/exercises/all"
#define GET_EXERCISE_DETAILS_PATH "/api/exercises"
#define SAVE_PROGRESS_PATH "/api/exercises"
#define EXECUTE_TEST_PATH "/api/exercises"
#define CONNECTION_TIMEOUT_MS 5000

typedef struct 
{
	int id;
    char *title;
    int progress; //-1 if not logged in
} ExerciseSimplified;

char *getAdditionalHeaderStringWithAuthToken();
static char* getStringCopy(const char *original);
int loginRequest(const char *username, const char *password);
int logoutRequest();
int registerRequest(const char *name, const char *email, const char *username, const char *password);
int getExercisesListRequest(ExerciseSimplified *exercises_list[], size_t *numberOfExercises);
int getExerciseDetailsRequest(int exercise_id, tic_exercise *exercise);
int parseExerciseTestsReceived(cJSON *exercise_element, tic_exercise *ticExercise);
int saveProgressRequest(Buffer exercise_data, char *code, int exercise_id);
int sendCodeToServerAndGetTestsResults(int exerciseId, char *code, tic_exercise *ticExercise);



#endif
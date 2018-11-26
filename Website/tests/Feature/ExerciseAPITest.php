<?php

namespace Tests\Feature;

use Tests\TestCase;

class ExerciseTest extends TestCase
{
    /**
     * Generic method used for make log in to user with username and password given.
     *
     * @return auth_token the authentication token that can be used in future communication for user identification
     */
    public function makeLoginForUser($username, $password)
    {
        $login_response = $this->call('POST', '/api/login', ['username' => $username, 'password' => $password]);
        $login_response_array = $login_response->decodeResponseJson();

        return $login_response_array['auth_token'];
    }

    //Get Exercises list request Tests

    /**
     * Generic method used for testing get all exercises request.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestGetAllExercises($headers, $expected_response_code, $number_exercises_received, $array_exercises_received)
    {
        $response = $this->get('/api/exercises/all', $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertTrue(array_key_exists('exercises', $response_array));
        $this->assertEquals(count($response_array['exercises']), $number_exercises_received);
        $this->assertTrue($response_array['exercises'] == $array_exercises_received);
    }

    /**
     * Tests if get all exercises request return all and just public exercises, without student logged in.
     */
    public function testGetAllPublicExercisesWithoutLogin()
    {
        $headers = [];
        $expected_response_code = 0;
        $number_exercises_received = 2;
        $excepted_array_exercises_received = array(
            array('id' => '1', 'title' => 'Exercise1Title', 'progress' => '0'),
            array('id' => '2', 'title' => 'Exercise2Title', 'progress' => '0'),
        );
        $this->genericTestGetAllExercises(
            $headers,
            $expected_response_code,
            $number_exercises_received,
            $excepted_array_exercises_received
        );
    }

    /**
     * Tests if get all exercises request return all and just public exercises, with student logged in but no permissions to any private exercise.
     */
    public function testGetAllPublicExercisesWithLogInButNoPermissions()
    {
        //make login to get auth token used in the get request of all exercises in order to get both public and private exercises to which student has permissions (0 in this case)
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db2', 'password_already_in_db2')];

        $expected_response_code = 0;
        $number_exercises_received = 2;
        $excepted_array_exercises_received = array(
            array('id' => '1', 'title' => 'Exercise1Title', 'progress' => '0'),
            array('id' => '2', 'title' => 'Exercise2Title', 'progress' => '0'),
        );
        $this->genericTestGetAllExercises(
            $headers,
            $expected_response_code,
            $number_exercises_received,
            $excepted_array_exercises_received
        );
    }

    /**
     * Tests if get all exercises request return all public exercises plus the private exercises that the logged in student has access.
     */
    public function testGetAllPublicPlusPrivateExercisesWithLogIn()
    {
        //make login to get auth token used in the get request of all exercises in order to get both public and private exercises to which user has permissions (2+1 in this case)
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];

        $expected_response_code = 0;
        $number_exercises_received = 3;
        $excepted_array_exercises_received = array(
        array('id' => '1', 'title' => 'Exercise1Title', 'progress' => '50'),
        array('id' => '2', 'title' => 'Exercise2Title', 'progress' => '0'),
        array('id' => '3', 'title' => 'Exercise3Title', 'progress' => '0'),
        );
        $this->genericTestGetAllExercises(
            $headers,
            $expected_response_code,
            $number_exercises_received,
            $excepted_array_exercises_received
        );
    }

    //Get Exercises details request Tests

    /**
     * Generic method used for testing get exercise details request.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestGetExerciseDetails($exercise_id, $input, $expected_response_code, $number_elements_received)
    {
        $response = $this->call('GET', '/api/exercises/'.$exercise_id);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
    }

    /**
     * Tests if get exercise details for a non existing exercise returns response code 1, indicating can't access the exercise(it can be for permissions or for non existing that's the case).
     */
    public function testGetExerciseDetailsForNonExistingExercise()
    {
        $this->genericTestGetExerciseDetails(0, [], 1, 1);
    }

    /**
     * Tests if get exercise details for a private exercise without being logged in returns response code 1, indicating can't access the exercise(it can be for permissions(that's the case) or for non existing).
     */
    public function testGetPrivateExerciseDetailsWithoutBeingLoggedIn()
    {
        $this->genericTestGetExerciseDetails(3, [], 1, 1);
    }

    /**
     * Tests if get exercise details for a private exercise without being logged in returns response code 1, indicating can't access the exercise(it can be for permissions(that's the case) or for non existing).
     */
    public function testGetPrivateExerciseDetailsWithoutPermissions()
    {
        //log in with user 2 that has no permissions for exercise 3 that is private
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db2', 'password_already_in_db2')];

        $input = [];
        $response = $this->get('/api/exercises/3', $input, $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('exercise', $response_array));
        $this->assertFalse(array_key_exists('tests', $response_array));
    }

    /**
     * Tests if get exercise details for a private exercise with being logged but no permissions to that exercise returns response code 1, indicating can't access the exercise(it can be for permissions(that's the case) or for non existing).
     */
    public function testGetPrivateExerciseDetailsLoggedInAndWithPermissions()
    {
        //log in with user 1 that has permissions for exercise 3 that is private
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];

        $response = $this->get('/api/exercises/3', $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('exercise', $response_array));
        $this->assertTrue(array_key_exists('tests', $response_array));
        $this->assertEquals(count($response_array['tests']), 2);
        $excepted_array_exercise_details_received = array(array(
            'creator_name' => 'name',
            'title' => 'Exercise3Title',
            'image_base64' => 'Exercise3ImageBase64',
            'description' => 'Exercise3Description',
            'progress' => '0',
            'feup8_file' => '', ));
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['exercise']);
        $excepted_array_exercise_tests_received = array(
            array('id' => '5', 'title' => 'test_sum_correct', 'hint' => 'Test1HintExercise3', 'test_code' => 'ZnVuY3Rpb24gdGVzdF9zdW1fY29ycmVjdCgpCmx1YXVuaXQuYXNzZXJ0RXF1YWxzKHN1bSgzLDQpICwgNykKbHVhdW5pdC5hc3NlcnRFcXVhbHMoc3VtKDQsMykgLCA3KQpsdWF1bml0LmFzc2VydEVxdWFscyhzdW0oMywtNCkgLCAtMSkKZW5k'),
            array('id' => '6', 'title' => 'test_sum_correct2', 'hint' => 'Test2HintExercise3', 'test_code' => 'ZnVuY3Rpb24gdGVzdF9zdW1fY29ycmVjdDIoKQpsdWF1bml0LmFzc2VydEVxdWFscyhzdW0oMyw0KSAsIDcpCmx1YXVuaXQuYXNzZXJ0RXF1YWxzKHN1bSg0LDMpICwgNykKbHVhdW5pdC5hc3NlcnRFcXVhbHMoc3VtKDMsLTQpICwgLTEpCmVuZA=='), );
        $this->assertEquals($excepted_array_exercise_tests_received, $response_array['tests']);
    }

    /**
     * Tests if get exercise details for a public exercise, expecting response code 0.
     */
    public function testGetPublicExerciseDetails()
    {
        $response = $this->call('GET', '/api/exercises/2');
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('exercise', $response_array));
        $this->assertTrue(array_key_exists('tests', $response_array));
        $this->assertEquals(count($response_array['tests']), 2);
        $excepted_array_exercise_details_received = array(array(
            'creator_name' => 'name',
            'title' => 'Exercise2Title',
            'image_base64' => 'Exercise2ImageBase64',
            'description' => 'Exercise2Description',
            'progress' => '0',
            'feup8_file' => '',
        ));
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['exercise']);
        $excepted_array_exercise_tests_received = array(
            array('id' => '3', 'title' => 'test_sum_failing', 'hint' => 'Test1HintExercise2', 'test_code' => 'ZnVuY3Rpb24gdGVzdF9zdW1fZmFpbGluZygpCmx1YXVuaXQuYXNzZXJ0RXF1YWxzKHN1bSgzLDQpICwgOCkKbHVhdW5pdC5hc3NlcnRFcXVhbHMoc3VtKDQsMykgLCA5KQpsdWF1bml0LmFzc2VydEVxdWFscyhzdW0oMywtNCkgLCAtNykKZW5k'),
            array('id' => '4', 'title' => 'test_sum_failing2', 'hint' => 'Test2HintExercise2', 'test_code' => 'ZnVuY3Rpb24gdGVzdF9zdW1fZmFpbGluZzIoKQpsdWF1bml0LmFzc2VydEVxdWFscyhzdW0oMyw0KSAsIDgpCmx1YXVuaXQuYXNzZXJ0RXF1YWxzKHN1bSg0LDMpICwgOSkKbHVhdW5pdC5hc3NlcnRFcXVhbHMoc3VtKDMsLTQpICwgLTcpCmVuZA=='), );
        $this->assertEquals($excepted_array_exercise_tests_received, $response_array['tests']);
    }

    //Test handleTestStudentCode

    //Test saveExerciseProgress

    /**
     * Generic method used for testing saveExerciseProgress method.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestSaveExerciseProgress($exercise_id, $number_elements_received, $expected_response_code, $parametersArray)
    {
        $response = $this->call('POST', '/api/exercises/'.$exercise_id.'/save', $parametersArray, [], [], []);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
    }

    /**
     * Tests if saveExerciseProgress method returns error code 2 when mandatory code paramenter is not sent.
     */
    public function testSaveExerciseProgressWithoutMandatoryCodeParameter()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 2;
        $parametersArray = ['exercise_data' => 'exercise_data'];

        $this->genericTestSaveExerciseProgress($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if saveExerciseProgress method returns error code 2 when mandatory exercise_data paramenter is not sent.
     */
    public function testSaveExerciseProgressWithoutMandatoryExerciseDataParameter()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 2;
        $parametersArray = ['code' => 'code'];

        $this->genericTestSaveExerciseProgress($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if saveExerciseProgress method returns error code 2 when mandatory paramenters are not sent.
     */
    public function testSaveExerciseProgressWithoutMandatoryParameters()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 2;
        $parametersArray = [];

        $this->genericTestSaveExerciseProgress($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if saveExerciseProgress method returns error code 1 when user not logged in.
     */
    public function testSaveExerciseProgressWithoutLogIn()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 1;
        $parametersArray = ['code' => 'code', 'exercise_data' => 'exercise_data'];

        $this->genericTestSaveExerciseProgress($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if saveExerciseProgress method returns error code 1 when user logged in but no permissions to access exercise.
     */
    public function testSaveExerciseProgressWithoutPermissionsToExercise()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 1;
        $parametersArray = ['code' => 'code', 'exercise_data' => 'exercise_data'];

        //log in with user 2 that has no permissions to exercise 3
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db2', 'password_already_in_db2')];
        $headers = $this->transformHeadersToServerVars($headers);

        $response = $this->call('POST', '/api/exercises/'.$exercise_id.'/save', $parametersArray, [], [], $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
    }

    /**
     * Tests if saveExerciseProgress method returns code 0 when user logged in, with permissions to access exercise and no errors.
     */
    public function testSaveExerciseProgressSuccessfully()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 0;
        $parametersArray = ['code' => 'ZnVuY3Rpb24gc3VtKG51bTEsIG51bTIpDQogICAgICAgIHJldHVybiBudW0xICsgbnVtMjsNCiAgICAgZW5k', 'exercise_data' => 'exercise_data'];

        //log in with user 1 that has permissions to exercise 3
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];
        $headers = $this->transformHeadersToServerVars($headers);

        $response = $this->call('POST', '/api/exercises/'.$exercise_id.'/save', $parametersArray, [], [], $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
    }

    /**
     * Tests if saveExerciseProgress method returns code 0 when user logged in, with permissions to access exercise and no errors.
     * This time already exists an exerciseStudent entry already in db, and this should averride it.
     */
    public function testSaveExerciseProgressSuccessfullyRepeated()
    {
        $this->testSaveExerciseProgressSuccessfully();
        $this->testSaveExerciseProgressSuccessfully();
    }

    //Test handleTestStudentCode

    /**
     * Generic method used for testing handleTestStudentCode method.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestHandleTestStudentCode($exercise_id, $number_elements_received, $expected_response_code, $parametersArray)
    {
        $response = $this->call('GET', '/api/exercises/'.$exercise_id.'/test', $parametersArray);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
    }

    /**
     * Tests if handleTestStudentCode method returns error code 2 when mandatory code paramenter is not sent.
     */
    public function testHandleTestStudentCodeWithoutMandatoryCodeParameter()
    {
        $exercise_id = 1;
        $number_elements_received = 1;
        $expected_response_code = 2;
        $parametersArray = [];

        $this->genericTestHandleTestStudentCode($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if handleTestStudentCode method returns error code 1 when has no permissions to access exercise tests.
     */
    public function testHandleTestStudentCodeWithoutPermissionToAccessExerciseTests()
    {
        $exercise_id = 3;
        $number_elements_received = 1;
        $expected_response_code = 1;
        $parametersArray = ['code' => 'code'];

        $this->genericTestHandleTestStudentCode($exercise_id, $number_elements_received, $expected_response_code, $parametersArray);
    }

    /**
     * Tests if handleTestStudentCode method returns tests_global_state -1 when student code has syntatic errors.
     */
    public function testHandleTestStudentCodeWitPermissionToAccessExerciseTestsButCodeHasSyntacticErrors()
    {
        $exercise_id = 3;
        $number_elements_received = 2;
        $expected_response_code = 0;
        $expected_tests_global_state = -1;
        //log in with user 1 that has permissions for exercise 3 that is private
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];
        $headers = $this->transformHeadersToServerVars($headers);

        $response = $this->call('GET', '/api/exercises/'.$exercise_id.'/test', ['code' => 'codeWithSyntacticErrors'], [], [], $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals($response_array['tests_global_state'], $expected_tests_global_state);
    }

    /**
     * Tests if handleTestStudentCode method returns tests_global_state 0 and the corrsponding tests results when student code was testes correctly.
     */
    public function testHandleTestStudentCodeWithPermissionToAccessExerciseTestsAndNoSysntaticErrors()
    {
        $exercise_id = 3;
        $number_elements_received = 3;
        $expected_response_code = 0;
        $expected_tests_global_state = 0;
        $expected_tests_results = ['test_sum_correct' => true, 'test_sum_correct2' => true];

        //log in with user 1 that has permissions for exercise 3 that is private
        $headers = ['Authorization' => 'Bearer '.$this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];
        $headers = $this->transformHeadersToServerVars($headers);
        //code = function sum(num1, num2) \n return num1 + num2; \n end
        $response = $this->call('GET', '/api/exercises/'.$exercise_id.'/test', ['code' => 'ZnVuY3Rpb24gc3VtKG51bTEsIG51bTIpDQogICAgICAgIHJldHVybiBudW0xICsgbnVtMjsNCiAgICAgZW5k'], [], [], $headers);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals(count($response_array), $number_elements_received);
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals($response_array['tests_global_state'], $expected_tests_global_state);
        $this->assertEquals($response_array['tests_results'], $expected_tests_results);
    }
}

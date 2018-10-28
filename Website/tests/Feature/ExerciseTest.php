<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class ExerciseTest extends TestCase
{
     /**
     * Generic method used for make log in to user with username and password given
     * @return auth_token The authentication token that can be used in future communication for user identification.
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
    public function genericTestGetAllExercises($input, $expected_response_code, $number_exercises_received, $array_exercises_received)
    {
        $response = $this->call('GET', '/api/exercises/all', $input);
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
        $input = [];
        $expected_response_code = 0;
        $number_exercises_received = 2;
        $excepted_array_exercises_received = array(
            array("id"=>"1","title"=>"Exercise1Title","progress"=>"50"),
            array("id"=>"2","title"=>"Exercise2Title","progress"=>"0")
        );
        $this->genericTestGetAllExercises( $input, $expected_response_code, $number_exercises_received, 
            $excepted_array_exercises_received);
    }

    /**
     * Tests if get all exercises request return all and just public exercises, with student logged in but no permissions to any private exercise.
     */
    public function testGetAllPublicExercisesWithLogInButNoPermissions()
    {
        //make login to get auth token used in the get request of all exercises in order to get both public and private exercises to which student has permissions (0 in this case)
        $input = ['auth_token' => $this->makeLoginForUser('user_already_in_db2', 'password_already_in_db2')];
      
        $expected_response_code = 0;
        $number_exercises_received = 2;
        $excepted_array_exercises_received = array(
            array("id"=>"1","title"=>"Exercise1Title","progress"=>"50"),
            array("id"=>"2","title"=>"Exercise2Title","progress"=>"0")
        );
        $this->genericTestGetAllExercises( $input, $expected_response_code, $number_exercises_received, 
            $excepted_array_exercises_received);
    }

    /**
     * Tests if get all exercises request return all public exercises plus the private exercises that the logged in student has access.
     */
    public function testGetAllPublicPlusPrivateExercisesWithLogIn()
    {
        //make login to get auth token used in the get request of all exercises in order to get both public and private exercises to which user has permissions (2+1 in this case)
        $input = ['auth_token' => $this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];

        $expected_response_code = 0;
        $number_exercises_received = 3;
        $excepted_array_exercises_received = array(
        array("id"=>"1","title"=>"Exercise1Title","progress"=>"50"),
        array("id"=>"2","title"=>"Exercise2Title","progress"=>"0"),
        array("id"=>"3","title"=>"Exercise3Title","progress"=>"0")
        );
        $this->genericTestGetAllExercises( $input, $expected_response_code, $number_exercises_received, 
            $excepted_array_exercises_received);
    }



    //Get Exercises details request Tests

    /**
     * Generic method used for testing get exercise details request.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestGetExerciseDetails($exercise_id, $input, $expected_response_code, $number_elements_received)
    {
        $response = $this->call('GET', "/api/exercise/" . $exercise_id);
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
        $input = ['auth_token' => $this->makeLoginForUser('user_already_in_db2', 'password_already_in_db2')];
      
        $this->genericTestGetExerciseDetails(0, $input, 1, 3);
        $response = $this->call('GET', '/api/exercise/3', $input);
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
        $input = ['auth_token' => $this->makeLoginForUser('user_already_in_db', 'password_already_in_db')];
      
        $response = $this->call('GET', '/api/exercise/3', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('exercise', $response_array));
        $this->assertTrue(array_key_exists('tests', $response_array));
        $this->assertEquals(count($response_array['tests']), 2);
        $excepted_array_exercise_details_received = array(
            "creator_name"=>"name",
            "title"=>"Exercise3Title",
            "image_base64"=>"Exercise3ImageBase64",
            "description"=>"Exercise3Description",
            "progress"=>"0");
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['exercise']);
        $excepted_array_exercise_tests_received = array(
            array("id"=>"5", "title"=>"Test1TitleExercise3", "hint"=>"Test1HintExercise3", "test_code_base64"=>"Test1TestCodeExercise3"),
            array("id"=>"6", "title"=>"Test2TitleExercise3", "hint"=>"Test2HintExercise3", "test_code_base64"=>"Test2TestCodeExercise3"));
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['tests']);
    }

    /**
     * Tests if get exercise details for a public exercise, expecting response code 0. 
     */
    public function testGetPublicExerciseDetails()
    {
        $response = $this->call('GET', '/api/exercise/2', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('exercise', $response_array));
        $this->assertTrue(array_key_exists('tests', $response_array));
        $this->assertEquals(count($response_array['tests']), 2);
        $excepted_array_exercise_details_received = array(
            "creator_name"=>"name",
            "title"=>"Exercise2Title",
            "image_base64"=>"Exercise2ImageBase64",
            "description"=>"Exercise2Description",
            "progress"=>"0");
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['exercise']);
        $excepted_array_exercise_tests_received = array(
            array("id"=>"3", "title"=>"Test1TitleExercise2", "hint"=>"Test1HintExercise2", "test_code_base64"=>"Test1TestCodeExercise2"),
            array("id"=>"4", "title"=>"Test2TitleExercise2", "hint"=>"Test2HintExercise2", "test_code_base64"=>"Test2TestCodeExercise2"));
        $this->assertEquals($excepted_array_exercise_details_received, $response_array['tests']);
    }
}

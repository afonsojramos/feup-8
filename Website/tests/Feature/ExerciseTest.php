<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class ExerciseTest extends TestCase
{
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
        $login_response = $this->call('POST', '/api/login', ['username' => 'user_already_in_db2', 'password' => 'password_already_in_db2']);
        $login_response_array = $login_response->decodeResponseJson();
        $input = ['auth_token' => $login_response_array['auth_token']];

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
        $login_response = $this->call('POST', '/api/login', ['username' => 'user_already_in_db', 'password' => 'password_already_in_db']);
        $login_response_array = $login_response->decodeResponseJson();
        $input = ['auth_token' => $login_response_array['auth_token']];

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
     * This
     *
     */
    public function testGetExerciseDetails()
    {
        //test get exercise datails from a non existing exercise
        //test get exercise datails from an exercise private without permissions logged in
        //test get exercise datails from an exercise private not logged in and without permissions
        //test get exercise datails from an exercise private logged in and with permissions

       /* $response = $this->call('GET', '/api/exercise/1');
        $response->assertStatus(200);
       /* $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertFalse(array_key_exists('exercises', $response_array));*/
       
        
    }

}

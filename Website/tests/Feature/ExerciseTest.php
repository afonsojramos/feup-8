<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class ExerciseTest extends TestCase
{
    /**
     * This
     *
     */
    public function testGetAllPublicExercises()
    {
        //test with 0 exercises
        //test get all public exercises without login
        //test get all public exercises with login but no permission for more
        //test get all public exercises + private for logged in

       /* $response = $this->call('GET', '/api/exercises/all');
        $response->assertStatus(200);
       /* $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertFalse(array_key_exists('exercises', $response_array));*/
     

    }


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

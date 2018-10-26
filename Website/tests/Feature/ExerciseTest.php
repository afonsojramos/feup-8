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

        $response = $this->call('GET', '/api/exercises/all');
        $response->assertStatus(200);
       /* $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertFalse(array_key_exists('exercises', $response_array));*/
        array_diff($response->decodeResponseJson(), json_decode(
        {
            "response_code": 0,
            "exercises":
            [
                {
                    "id": 1,
                    "title": "Make a supermario game.",
                    "progress": 0
                },
                {
                    "id": 2,
                    "title": "Make a sonic game.",
                    "progress": 10
                },
                {
                    "id": 3,
                    "title": "Make a 3rd person platform shooter game.",
                    "progress": 100
                }
            ]
        }));

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

        $response = $this->call('GET', '/api/exercise/1');
        $response->assertStatus(200);
       /* $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertFalse(array_key_exists('exercises', $response_array));*/
        echo $response->decodeResponseJson();
        array_diff($response->decodeResponseJson(), json_decode(
        `{
            "response_code": 0,
            "exercise": [
                {
                    "title": "sit amet metus.",
                    "description": "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Curabitur sed tortor. Integer aliquam adipiscing lacus. Ut nec urna et arcu imperdiet ullamcorper. Duis at lacus. Quisque purus sapien, gravida non, sollicitudin a, malesuada id, erat.",
                    "image_base64": "1.png",
                    "creator_name": "Utilizador Um",
                    "progress": "0",
                    "feup8_file": ""
                }
            ],
            "tests": [
                {
                    "id": "1",
                    "title": "Duis elementum,",
                    "test_code": "Suspendisse sed dolor. Fusce mi lorem, vehicula et, rutrum eu, ultrices sit amet, risus. Donec",
                    "hint": "ac, fermentum vel, mauris. Integer sem elit, pharetra ut,"
                }
            ]
        }`));
        
    }

}

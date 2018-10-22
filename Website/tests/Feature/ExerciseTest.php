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
        $response = $this->call('GET', '/api/exercise/1');
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertFalse(array_key_exists('exercises', $response_array));
        
    }

        /**
     * This
     *
     */
    public function testRegisterRepeated()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'password' => 'password', 
            'name' => 'name', 'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }

    /**
     * A basic test example.
     *
     */
    public function testLogin()
    {
        $response = $this->call('POST', '/api/login', ['username' => 'user1', 'password' => '$2y$10$vOp6qnGv9Ae/0NdmD/D7fudXzoU6CltbYSSrIqK2/ARmTUBgzo2gK']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('auth_token', $response_array));
    }
}

<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class ExampleTest extends TestCase
{
    /**
     * A basic test example.
     *
     * @return void
     */
    public function testBasicTest()
    {
        $response = $this->call('POST', '/api/login', ['username' => 'user1', 'password' => '$2y$10$vOp6qnGv9Ae/0NdmD/D7fudXzoU6CltbYSSrIqK2/ARmTUBgzo2gK']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('auth_token', $response_array));
    }

    public function testRegister()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'password' => 'password', 
            'name' => 'name', 'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        //$this->assertTrue(array_key_exists('auth_token', $response_array));
    }
}

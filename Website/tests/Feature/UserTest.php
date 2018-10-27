<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class UserTests extends TestCase
{
    /**
     * Tests if a register without email is rejected.
     */
    public function testRegisterWithoutEmail()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'password' => 'password', 
            'name' => 'name']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }

    /**
     * Tests if a register without name is rejected.
     */
    public function testRegisterWithoutName()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'password' => 'password', 
            'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }

    /**
     * Tests if a register without password is rejected.
     */
    public function testRegisterWithoutPassword()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'name' => 'name', 
            'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }   
    
    /**
     * Tests if a register without username is rejected.
     */
    public function testRegisterWithoutUserName()
    {
        $response = $this->call('POST', '/api/register', ['password' => 'password', 'name' => 'name', 
            'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }     

    /**
     * Tests if a successfull register can be done, all the necessary parameters are given, and for the first time(not repeated username or email).
     */
    public function testRegister()
    {
        $response = $this->call('POST', '/api/register', ['username' => 'user1', 'password' => 'password', 
            'name' => 'name', 'email' => 'email']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 0);
        $this->assertTrue(array_key_exists('auth_token', $response_array));
    }

    /**
     * Tests if a repeated register is rejected. The username or email are already in the db.
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
     * Tests if login fails with wrong password for given username.
     */
    public function testLoginFailForWrongPassword()
    {
        $response = $this->call('POST', '/api/login', ['username' => 'user1', 'password' => 'passwordWrong']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }

    /**
     * Tests if login fails with inexistent username.
     */
    public function testLoginFailForInexistentUsername()
    {
        $response = $this->call('POST', '/api/login', ['username' => 'userNotExistent', 'password' => 'password']);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], 1);
        $this->assertFalse(array_key_exists('auth_token', $response_array));
    }

    /**
     * Tests if a successfull login can be done, all the necessary parameters are given.
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

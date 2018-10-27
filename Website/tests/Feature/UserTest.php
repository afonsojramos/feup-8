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
        $input = ['username' => 'user1', 'password' => 'password', 
        'name' => 'name'];
        testRegister($input, 1, false);
    }

    /**
     * Tests if a register without name is rejected.
     */
    public function testRegisterWithoutName()
    {
        $input = ['username' => 'user1', 'password' => 'password', 
        'email' => 'email'];
        testRegister($input, 1, false);
    }

    /**
     * Tests if a register without password is rejected.
     */
    public function testRegisterWithoutPassword()
    {
        $input = ['username' => 'user1', 'name' => 'name', 
        'email' => 'email'];
        testRegister($input, 1, false);
    }   
    
    /**
     * Tests if a register without username is rejected.
     */
    public function testRegisterWithoutUserName()
    {
        $input = ['password' => 'password', 'name' => 'name', 
        'email' => 'email'];
        testRegister($input, 1, false);
    }     

    /**
     * Tests if a successfull register can be done, all the necessary parameters are given, and for the first time(not repeated username or email).
     */
    public function testRegisterCorrectly()
    {
        $input = ['username' => 'user1', 'password' => 'password', 
        'name' => 'name', 'email' => 'email'];
        testRegister($input, 0, true);
    }

    /**
     * Generic method used for testing register feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function testRegister($input, $expected_response_code, $should_succeed)
    {
        $response = $this->call('POST', '/api/register', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals(array_key_exists('auth_token', $response_array), $should_succeed);
    }

    /**
     * Tests if a repeated register is rejected. (It should fail because the username or email are already in the db).
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
        $input = ['username' => 'user1', 'password' => 'passwordWrong'];
        testLogin($input, 1, false);
    }

    /**
     * Tests if login fails with inexistent username.
     */
    public function testLoginFailForInexistentUsername()
    {
        $input = ['username' => 'userNotExistent', 'password' => 'password'];
        testLogin($input, 1, false);
    }

    /**
     * Tests if a successfull login can be done, all the necessary parameters are given.
     */
    public function testLoginCorrectly()
    {
        $input = ['username' => 'user1', 'password' => '$2y$10$vOp6qnGv9Ae/0NdmD/D7fudXzoU6CltbYSSrIqK2/ARmTUBgzo2gK'];
        testLogin($input, 0, true);
    }

    /**
     * Generic method used for testing login feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     * */
    public function testLogin($input, $expected_response_code, $should_succeed)
    {
        $response = $this->call('POST', '/api/login', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals(array_key_exists('auth_token', $response_array), $should_succeed);
    }
}

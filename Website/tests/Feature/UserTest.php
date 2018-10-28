<?php

namespace Tests\Feature;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;

class UserTests extends TestCase
{
    /* Register tests
    
    /**
     * Generic method used for testing register feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestRegister($input, $expected_response_code, $should_succeed, $numberOfElementsReceived)
    {
        $response = $this->call('POST', '/api/register', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals(array_key_exists('auth_token', $response_array), $should_succeed);
        $this->assertEquals(count($response_array), $numberOfElementsReceived);
    }

    /**
     * Tests if a register without email is rejected.
     */
    public function testRegisterWithoutEmail()
    {
        $input = ['username' => 'user_register', 'password' => 'password_register', 
            'name' => 'name_register'];
        $this->genericTestRegister($input, 1, false, 1);
    }

    /**
     * Tests if a register without name is rejected.
     */
    public function testRegisterWithoutName()
    {
        $input = ['username' => 'user_register', 'password' => 'password_register', 
            'email' => 'email_register'];
        $this->genericTestRegister($input, 1, false, 1);
    }

    /**
     * Tests if a register without password is rejected.
     */
    public function testRegisterWithoutPassword()
    {
        $input = ['username' => 'user_register', 'name' => 'name_register', 
            'email' => 'email_register'];
        $this->genericTestRegister($input, 1, false, 1);
    }   
    
    /**
     * Tests if a register without username is rejected.
     */
    public function testRegisterWithoutUserName()
    {
        $input = ['password' => 'password_register', 'name' => 'name_register', 
            'email' => 'email_register'];
        $this->genericTestRegister($input, 1, false, 1);
    }     

    /**
     * Tests if a successfull register can be done, all the necessary parameters are given, and for the first time(not repeated username or email).
     */
    public function testRegisterCorrectly()
    {
        $input = ['username' => 'user_register', 'password' => 'password_register', 
            'name' => 'name_register', 'email' => 'email_register'];
        $this->genericTestRegister($input, 0, true, 2);
    }

     /**
     * Tests if a repeated register is rejected. (It should fail because the username is already in the db).
     */
    public function testRegisterRepeatedUsername()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'password', 
            'name' => 'name', 'email' => 'email'];
        testRegister($input, 1, false, 1);
    }

    /**
     * Tests if a repeated register for email is rejected. (It should fail because the email is already in the db).
     */
    public function testRegisterRepeatedEmail()
    {
        $input = ['username' => 'username', 'password' => 'password', 
            'name' => 'name', 'email' => 'email_already_in_db'];
        testRegister($input, 1, false, 1);
    }



    /* Login tests

    /**
     * Generic method used for testing login feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     * */
    public function genericTestLogin($input, $expected_response_code, $should_succeed, $numberOfElementsReceived)
    {
        $response = $this->call('POST', '/api/login', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals(array_key_exists('auth_token', $response_array), $should_succeed);
        $this->assertEquals(count($response_array), $numberOfElementsReceived);
    }

    /**
     * Tests if login fails with wrong password for given username.
     */
    public function testLoginFailForWrongPassword()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'wrong_password'];
        $this->genericTestLogin($input, 1, false, 1);
    }

    /**
     * Tests if login fails with inexistent username.
     */
    public function testLoginFailForInexistentUsername()
    {
        $input = ['username' => 'user_not_in_db', 'password' => 'password'];
        $this->genericTestLogin($input, 1, false, 1);
    }

    /**
     * Tests if a successfull login can be done, all the necessary parameters are given.
     */
    public function testLoginCorrectly()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'password_already_in_db'];
        $this->genericTestLogin($input, 0, true, 2);
    }

    

    // Logout Tests

    /**
     * Generic method used for testing logout feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     * */
    public function genericTestLogout($input, $expected_response_code, $numberOfElementsReceived)
    {
        $response = $this->call('POST', '/api/logout', $input);
        $response->assertStatus(200);
        $response_array = $response->decodeResponseJson();
        $this->assertEquals($response_array['response_code'], $expected_response_code);
        $this->assertEquals(count($response_array), $numberOfElementsReceived);
    }

    /**
     * Tests if a logout is rejected if user not logged in
     */
    public function testLogoutWithoutBeingLoggedIn()
    {
        $input = [];
        $this->genericTestLogout($input, 1, 1);
    }
   
    /**
     * Tests if a successfull logout can be done, all the necessary parameters are given.
     */
    public function testLogoutSuccessfully()
    {
        $login_response = $this->call('POST', '/api/login', ['username' => 'user_already_in_db', 'password' => 'password_already_in_db']);
        $login_response_array = $login_response->decodeResponseJson();
        $input = ['auth_token' => $login_response_array['auth_token']];
        $this->genericTestLogout($input, 0, 1);
    }
}
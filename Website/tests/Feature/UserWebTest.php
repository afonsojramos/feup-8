<?php

namespace Tests\Feature;

use Tests\TestCase;

class UserWebTests extends TestCase
{
    private $redirect_code = 302;

    /* Register tests

    /**
     * Generic method used for testing register feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestRegister($input, $redirect_to_url, $redirect_with)
    {
        $response = $this->call('POST', '/register', $input);
        $response->assertStatus($this->redirect_code);
        $response->assertRedirect($redirect_to_url, $redirect_with);
    }

    /**
     * Tests if a register without email is rejected.
     */
    public function testRegisterWithoutEmail()
    {
        $input = ['username' => 'user_register', 'password' => 'password_register',
            'name' => 'name_register', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Missing one or more elements: username, name, password, email']);
    }

    /**
     * Tests if a register without name is rejected.
     */
    public function testRegisterWithoutName()
    {
        $input = ['username' => 'user_register', 'password' => 'password_register',
            'email' => 'email_register', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Missing one or more elements: username, name, password, email']);
    }

    /**
     * Tests if a register without password is rejected.
     */
    public function testRegisterWithoutPassword()
    {
        $input = ['username' => 'user_register', 'name' => 'name_register',
            'email' => 'email_register', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Missing one or more elements: username, name, password, email']);
    }

    /**
     * Tests if a register without username is rejected.
     */
    public function testRegisterWithoutUserName()
    {
        $input = ['password' => 'password_register', 'name' => 'name_register',
            'email' => 'email_register', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Missing one or more elements: username, name, password, email']);
    }

    /**
     * Tests if a successfull register can be done, all the necessary parameters are given, and for the first time(not repeated username or email).
     */
    public function testRegisterCorrectly()
    {
        $input = ['username' => 'teacher_register', 'password' => 'password_register',
            'name' => 'name_register', 'email' => 'teacher_email_register', ];
        $this->genericTestRegister($input, '', []);
    }

    /**
     * Tests if a repeated register is rejected. (It should fail because the username is already in the db).
     */
    public function testRegisterRepeatedUsername()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'password',
            'name' => 'name', 'email' => 'email', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Username already exists!']);
    }

    /**
     * Tests if a repeated register for email is rejected. (It should fail because the email is already in the db).
     */
    public function testRegisterRepeatedEmail()
    {
        $input = ['username' => 'username', 'password' => 'password',
            'name' => 'name', 'email' => 'email_already_in_db', ];
        $this->genericTestRegister($input, '/register', ['msg', 'Error creating your account!']);
    }

    /* Login tests

    /**
     * Generic method used for testing login feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     * */
    public function genericTestLogin($input, $redirect_to_url, $redirect_with)
    {
        $response = $this->call('POST', '/login', $input);
        $response->assertStatus($this->redirect_code);
        $response->assertRedirect($redirect_to_url, $redirect_with);
    }

    /**
     * Tests if a login without username is rejected.
     */
    public function testLoginWithoutUsername()
    {
        $input = ['password' => 'password'];
        $this->genericTestLogin($input, '/login', ['msg', 'Missing username or password']);
    }

    /**
     * Tests if a login without username is rejected.
     */
    public function testLoginWithoutPassword()
    {
        $input = ['username' => 'user_already_in_db'];
        $this->genericTestLogin($input, '/login', ['msg', 'Missing username or password']);
    }

    /**
     * Tests if login fails with inexistent username.
     */
    public function testLoginFailForInexistentUsername()
    {
        $input = ['username' => 'user_not_in_db', 'password' => 'password'];
        $this->genericTestLogin($input, '/login', ['msg', "Username password doesn't exist"]);
    }

    /**
     * Tests if login fails with wrong password for given username.
     */
    public function testLoginFailForWrongPassword()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'wrong_password'];
        $this->genericTestLogin($input, '/login', ['msg', "Username password doesn't exist"]);
    }

    /**
     * Tests if a successfull login can be done, all the necessary parameters are given.
     */
    public function testLoginCorrectly()
    {
        $input = ['username' => 'user_already_in_db', 'password' => 'password_already_in_db'];
        $this->genericTestLogin($input, '', []);
    }

    //Probably not needed, laravel already does it
    // Logout Tests

    /*
     * Generic method used for testing logout feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     * */
  /*  public function genericTestLogout($input, $redirect_to_url, $redirect_with)
    {
        $response = $this->call('POST', '/logout', $input);
        $response->assertStatus($this->redirect_code);
        $response->assertRedirect($redirect_to_url, $redirect_with);
    }*/
    /*
     * Tests if a successfull logout can be done, all the necessary parameters are given.
     */
  /*  public function testLogoutSuccessfully()
    {
        $input = [];
        $this->genericTestLogin($input, "", []);
    }*/
}

<?php

namespace Tests\Feature;

use Tests\TestCase;
use App\User;

class TestWebTest extends TestCase
{
    private $redirect_code = 302;

    private function createUser($userIdToBeCreated)
    {
        $user = factory(User::class)->create(
            [
                'id' => $userIdToBeCreated,
                'username' => 'username'.$userIdToBeCreated,
                'email' => 'john'.$userIdToBeCreated.'@example.com',
                'password' => bcrypt('secret'),
                'isTeacher' => true,
            ]
        );
        $this->be($user);
    }

    public function testInvalidTestAsInput()
    {
        //$this->createUser(101);
        $input = ['form-test-code' => 'adasdasdasdasdasd', 'form-title' => 'sadasdasd'];
        $response = $this->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);

        $input = [];
        $response = $this->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testValidTestAsInput()
    {
        //$this->createUser(102);
        $input = ['form-test-code' => 'x = 1', 'form-title' => 'adasd'];
        $response = $this->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testEditExistingTest()
    {
        //$this->createUser(103);
        $input = ['form-test-code' => 'x = 1', 'form-title' => 'adasd'];
        $response = $this->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_code);

        $input = [];
        $response = $this->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testRemoveExistingTest()
    {
        //$this->createUser(104);
        $input = [];
        $response = $this->call('POST', '/exercise/1/edit/test/1/remove', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testRemoveNonExistingTests()
    {
        //$this->createUser(104);
        $input = [];
        $response = $this->call('POST', '/exercise/1/edit/test/4123123/remove', $input);
        $response->assertStatus($this->redirect_code);
        $response = $this->call('POST', '/exercise/1/edit/test/-4123123/remove', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testEditExercise()
    {
        //$this->createUser(105);
        $input = [];
        $response = $this->call('POST', '/exercise/1/edit', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testAddHintToTest()
    {
        //$this->createUser(105);
        $input = ['form-hint' => 'asdasdasdsa'];
        $response = $this->call('POST', '/exercise/1/edit/test/1/tip', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }
}

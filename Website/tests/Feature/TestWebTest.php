<?php

namespace Tests\Feature;

use Tests\TestCase;
use App\User;

class TestWebTest extends TestCase
{
    private $redirect_code = 302;
    private $redirect_forbidden = 403;

    private function authenticateUser($userIdToBeAuth)
    {
        $user = factory(User::class)->make(
            [
                'id' => $userIdToBeAuth,
                'username' => 'user_already_in_db',
                'email' => 'name',
                'password' => '$2y$10$CIMNPzE21s7KpyAoRuPL6OVnSq.4UE5XVJxvUsaExxpRCZJO3s8Iy',
                'isTeacher' => true,
            ]
        );

        $this->be($user);

        return $user;
    }

    public function testInvalidTestAsInput()
    {
        $user = $this->authenticateUser(1);
        $input = ['form-test-code' => 'adasdasdasdasdasd', 'form-title' => 'sadasdasd'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);

        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testValidTestAsInput()
    {
        $user = $this->authenticateUser(1);
        $input = ['form-test-code' => 'x = 1', 'form-title' => 'adasd'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/addTest', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testEditExistingTest()
    {
        $user = $this->authenticateUser(1);
        $input = ['form-test-code' => 'x = 1', 'form-title' => 'adasd'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_code);

        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testEditExistingTestAsNotCreator()
    {
        $user = $this->authenticateUser(10);
        $input = ['form-test-code' => 'x = 1', 'form-title' => 'adasd'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_forbidden);

        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testRemoveExistingTestWithoutBeingItsCreator()
    {
        $user = $this->authenticateUser(10);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/remove', $input);
        $response->assertStatus($this->redirect_forbidden);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testRemoveExistingTest()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/1/remove', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testRemoveNonExistingTests()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/4123123/remove', $input);
        $response->assertStatus($this->redirect_code);
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/-4123123/remove', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testAddHintToTest()
    {
        $user = $this->authenticateUser(1);
        $input = ['form-hint' => 'asdasdasdsa'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/2/tip', $input);
        $response->assertStatus($this->redirect_code);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }

    public function testAddHintToTestAsNotCreator()
    {
        $user = $this->authenticateUser(10);
        $input = ['form-hint' => 'asdasdasdsa'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit/test/2/tip', $input);
        $response->assertStatus($this->redirect_forbidden);
        //$response->assertRedirect($redirect_to_url, $redirect_with);
    }
}

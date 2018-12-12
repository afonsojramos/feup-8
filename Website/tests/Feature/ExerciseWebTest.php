<?php

namespace Tests\Feature;

use Tests\TestCase;
use App\User;

class ExerciseWebTests extends TestCase
{
    private $redirect_code = 302;
    private $success_code = 200;
    private $forbidden_code = 403;

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

    /**
     * Generic method used for testing creation of exercise feature.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericExerciseCreate($userIdToBeCreated, $input, $redirect_to_url, $redirect_with)
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

        $response = $this->call('POST', '/exercise/create', $input);
        $response->assertStatus($this->redirect_code);
        $response->assertRedirect($redirect_to_url, $redirect_with);
    }

    /**
     * Tests if an exercise creation without title is rejected.
     */
    public function testCreateExerciseWithoutTitle()
    {
        $input = ['form-description' => 'ExerciseDescription'];
        $this->genericExerciseCreate(60, $input, '/exercise/create', ['msg', 'Please fill all the fields.']);
    }

    public function viewExercisePage()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->call('GET', '/exercise/1', $input);
        $response->assertStatus($this->redirect_code);
    }

    /**
     * Tests if an exercise creation without title is rejected.
     */
    public function testCreateExerciseWithTitleThatExists()
    {
        $user = factory(User::class)->make(
            [
                'id' => 66,
                'username' => 'user_already_in_db',
                'email' => 'name',
                'password' => '$2y$10$CIMNPzE21s7KpyAoRuPL6OVnSq.4UE5XVJxvUsaExxpRCZJO3s8Iy',
                'isTeacher' => false,
            ]
        );
        $this->be($user);

        $input = ['form-title' => 'test_sum_correct', 'form-description' => 'ExerciseDescription'];
        $response = $this->actingAs($user)->call('POST', '/exercise/create', $input);
        $response->assertStatus($this->redirect_code);
    }

    /**
     * Tests if an exercise creation without being loggedin is rejected.
     */
    public function testCreateExerciseWithoutBeingLoggedIn()
    {
        $input = ['form-title' => 'ExerciseTitle', 'form-description' => 'ExerciseDescription'];
        $response = $this->call('POST', '/exercise/create', $input);
        $response->assertStatus($this->redirect_code);
    }

    /**
     * Tests if an exercise creation without being a teacher is rejected.
     */
    public function testCreateExerciseWithoutBeingATeacher()
    {
        $user = factory(User::class)->make(
            [
                'id' => 65,
                'username' => 'user_already_in_db',
                'email' => 'name',
                'password' => '$2y$10$CIMNPzE21s7KpyAoRuPL6OVnSq.4UE5XVJxvUsaExxpRCZJO3s8Iy',
                'isTeacher' => false,
            ]
        );
        $this->be($user);

        $input = ['form-title' => 'ExerciseTitle', 'form-description' => 'ExerciseDescription'];
        $response = $this->actingAs($user)->call('POST', '/exercise/create', $input);
        $response->assertStatus($this->redirect_code);
    }

    /**
     * Tests if an exercise creation without deecription is rejected.
     */
    public function testCreateExerciseWithoutDescription()
    {
        $input = ['form-title' => 'ExerciseTitle'];
        $this->genericExerciseCreate(61, $input, '/exercise/create', ['msg', 'Please fill all the fields.']);
    }

    /**
     * Tests if a successfull creation of exercise can be done, all the necessary parameters are given and the isPrivate is not set (meaning it should be public), and for the first time (title not duplicated).
     */
    public function testCreateExerciseCorrectlyWithIsPrivateSet()
    {
        $private = 'on';
        $input = ['form-title' => 'ExerciseTitle', 'form-description' => 'ExerciseDescription',
            'form-isPrivate' => $private, ];
        $this->genericExerciseCreate(62, $input, '/exercise/create', ['msg', 'Exercise created successfully.']);
    }

    /**
     * Tests if a successfull creation of exercise can be done, all the necessary parameters are given and the isPrivate is set (meaning it should be private), and for the first time (title not duplicated).
     */
    public function testCreateExerciseCorrectlyWithoutIsPrivateSet()
    {
        $input = ['form-title' => 'ExerciseTitle2', 'form-description' => 'ExerciseDescription'];
        $this->genericExerciseCreate(63, $input, '/exercise/create', ['msg', 'Exercise created successfully.']);
    }

    /**
     * Tests if an exercise with a duplicated title is rejected. (It should fail because there is already an exercise with the same title in the db).
     */
    public function testCreateExerciseDuplicatedTitle()
    {
        $input = ['form-title' => 'Exercise1Title', 'form-description' => 'ExerciseDescription'];
        $this->genericExerciseCreate(64, $input, '/exercise/create', ['msg', 'Sorry, there is already an exercise with that title. Please choose a different title.']);
    }

    public function testGetAllExercises()
    {
        $input = [];
        $response = $this->call('GET', '/exercises', $input);
        $response->assertStatus($this->success_code);
    }

    public function testGetAllExercisesAsUser()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('GET', '/exercises', $input);
        $response->assertStatus($this->success_code);
    }

    public function testGetAllExercisesFromUserUnauthenticated()
    {
        $input = [];
        $response = $this->call('GET', '/teacher/exercises', $input);
        $response->assertStatus($this->forbidden_code);
    }

    public function testGetAllExercisesFromUser()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('GET', '/teacher/exercises', $input);
        $response->assertStatus($this->success_code);
    }

    public function testEditExerciseAsItsCreator()
    {
        $user = $this->authenticateUser(1);
        $input = ['form-description' => 'xpto'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testEditExerciseWithoutInput()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testEditExerciseAsNotItsOwnCreator()
    {
        $user = $this->authenticateUser(2);
        $input = ['form-description' => 'xpto'];
        $response = $this->actingAs($user)->call('POST', '/exercise/1/edit', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testDeleteExerciseAsNotItsOwnCreator()
    {
        $user = $this->authenticateUser(2);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/2/delete', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testDeleteExerciseAsNotAuthenticatedUser()
    {
        $input = [];
        $response = $this->call('POST', '/exercise/2/delete', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testDeleteExerciseAsItsCreator()
    {
        $user = $this->authenticateUser(1);
        $input = [];
        $response = $this->actingAs($user)->call('POST', '/exercise/2/delete', $input);
        $response->assertStatus($this->redirect_code);
    }

    public function testcreateExercisePage()
    {
        $input = [];
        $response = $this->call('GET', '/exercise/create', $input);
        $response->assertStatus($this->success_code);
    }
}

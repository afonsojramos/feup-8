<?php

namespace Tests\Unit;

use Tests\TestCase;
use App\User;
use App\Http\Controllers\Web\UserController;

class UserTest extends TestCase
{
    /**
     * Tests if the function UserController::testCurrentlyLoggedInUserIdRetrieving returns the currently logged in user id correctly when a user is logged in.
     */
    public function testCurrentlyLoggedInUserIdRetrieving()
    {
        $user = factory(User::class)->create(
            [
                'id' => 50,
                'username' => 'username50',
                'email' => 'john@example.com',
                'password' => bcrypt('secret'),
                'isTeacher' => true,
            ]);

        $this->be($user);
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        $this->assertEquals($current_user_id, 50);
    }

    /**
     * Tests if the function UserController::testCurrentlyLoggedInUserIdRetrieving returns the currently logged in user id correctly when a user is not logged in (it should return 0).
     */
    public function testCurrentlyLoggedInUserIdRetrievingWithNoUserLoggedIn()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        $this->assertEquals($current_user_id, 0);
    }
}

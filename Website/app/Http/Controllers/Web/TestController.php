<?php

namespace App\Http\Controllers\Web;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use DB;

class TestController extends Controller
{
    /**
     * Adds a tip to a given unit test.
     *
     * @param $request the received request
     * @param $id the id of the test
     *
     * @return 403 if permissions error, 500 if DB error or 200 if success
     */
    public function addTipToExercise(Request $request, $id, $test_id)
    {
        /*if (!($request->ajax() || $request->pjax() || Auth::check())) {
            redirect('exercise/'.$id)->withErrors(['msg' => 'No Authorization to update.']);
        }*/

        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
        {
            return 'FORBIDDEN';
        }
        if ($request->has('form-hint'))
        {
            DB::table('Test')->where('id', $test_id)->update(['hint' => $request['form-hint']]);
        }

        return redirect('exercise/'.$id);
    }

    /**
     * Edits the code of a given unit test.
     *
     * @param $request the received request
     * @param $id the id of the exercise
     * @param $test_id the id of the test
     *
     * @return the exercise view on success, 'FORBIDDEN' on the authenticated user not being
     *             the creator of the exercise and exercise list with msg 'Test Code is not valid' on fail of validator
     */
    public function editTestCode(Request $request, $id, $test_id)
    {
        if ($request->has('form-title') && $request->has('form-test-code') && 0 == TestController::validateTest($request['form-test-code']))
        {
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
            {
                return 'FORBIDDEN';
            }

            DB::table('Test')->where('id', $test_id)->update(['test_code' => $request['form-test-code'], 'title' => $request['form-title']]);

            return redirect('exercise/'.$id);
        }

        return redirect('exercise/'.$id)->withErrors(['msg' => 'Test Code is Not Valid.']);
    }

    /**
     * Adds a unit test to an exercise.
     *
     * @param $request the received request
     * @param $id the id of the exercise
     *
     * @return the exercise view on success, 'FORBIDDEN' on the authenticated user not being
     *             the creator of the exercise and exercise list with msg 'Test Code is not valid' on fail of validator
     */
    public function addTestToExercise(Request $request, $id)
    {
        if ($request->has('form-title') && $request->has('form-test-code')
            && 0 == TestController::validateTest($request['form-test-code']))
        {
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
            {
                return 'FORBIDDEN';
            }

            DB::table('Test')->insert(
                    ['title' => $request['form-title'], 'test_code' => $request['form-test-code'],
                    'exercise_id' => $id, ]
                );

            return redirect('exercise/'.$id);
        }

        return redirect('exercise/'.$id)->withErrors(['msg' => 'Test Code is Not Valid.']);
    }

    /**
     * Removes a unit test from an exercise.
     *
     * @param $request the received request
     * @param $id the id of the exercise
     * @param $test_id the id of the test
     *
     * @return the exercise view on success, 'FORBIDDEN' on the authenticated user not being
     *             the creator of the exercise and exercise list with msg 'Sorry, there was an issue
     *             executing your request. If you believe this is an error, please contact system admin.' on error.
     */
    public function removeTest(Request $request, $id, $test_id)
    {
        try
        {
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
            {
                return 'FORBIDDEN';
            }

            DB::table('Test')->where('id', $test_id)->delete();
        }
        catch (\Exception $e)
        {
            return redirect('/exercise/'.$id)->withErrors(['msg' => 'Sorry, there was an issue executing your request. If you believe this is an error, please contact system admin.']);
        }

        return redirect('exercise/'.$id);
    }

    /**
     * Checks the validation of the code of a unit test using the conventions of luaunit.
     *
     * @param $text the received request
     *
     * @return "true" if code is in convention with luaunit and false if not
     */
    private function validateTest($text)
    {
        $filename = md5(uniqid(rand(), true)).'.lua';
        $file = fopen($filename, 'w');
        fwrite($file, $text);

        $cmd = 'luajit -bl '.$filename.' > /dev/null';
        $output = [];
        $ret;
        exec($cmd, $output, $ret);

        unlink($filename);

        return 0 != $ret;
    }
}

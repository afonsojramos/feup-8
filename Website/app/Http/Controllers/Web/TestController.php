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
        if ($request->has('form-hint'))
        {
            DB::table('Test')->where('id', $test_id)->update(['hint' => $request['form-hint']]);
        }

        return redirect('exercise/'.$id);
    }

    public function editTestCode(Request $request, $id, $test_id)
    {
        if ($request->has('form-title') && $request->has('form-test-code') && 0 == TestController::validateTest($request['form-test-code']))
        {
            DB::table('Test')->where('id', $test_id)->update(['test_code' => $request['form-test-code'], 'title' => $request['form-title']]);

            return redirect('exercise/'.$id);
        }

        return redirect('exercise/'.$id)->withErrors(['msg' => 'Test Code is Not Valid.']);
    }

    public function addTestToExercise(Request $request, $id)
    {
        if ($request->has('form-title') && $request->has('form-test-code')
            && 0 == TestController::validateTest($request['form-test-code']))
        {
            DB::table('Test')->insert(
                    ['title' => $request['form-title'], 'test_code' => $request['form-test-code'],
                    'exercise_id' => $id, ]
                );

            return redirect('exercise/'.$id);
        }

        return redirect('exercise/'.$id)->withErrors(['msg' => 'Test Code is Not Valid.']);
    }

    public function removeTest(Request $request, $id, $test_id)
    {
        DB::table('Test')->where('id', $test_id)->delete();

        return redirect('exercise/'.$id);
    }

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

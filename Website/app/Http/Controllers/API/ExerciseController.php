<?php

namespace App\Http\Controllers\API;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\LuaUnitExecutor;
use App\LuaUnitParser;
use Illuminate\Support\Facades\Auth;
use Validator;
use DB;

class ExerciseController extends Controller
{
    /**
     * This method will return the list of all non private exercises plus the private exercises that the user has access. Only some info, id and title are sent.
     *
     * @return A list of all available exercises in JSON, and the response code of 0 menig sucess. Response code 1 otherwise.
     */
    public function getAllExercises()
    {
        try
        {
            $exercises = DB::table('Exercise')
                ->selectRaw('id, title, 0 as progress')
                ->where('isPrivate', false);

            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 != $current_user_id)
            { //logged in
                $exercises_ids_in_progress = DB::table('ExerciseStudent')
                    ->selectRaw('exercise_id as id')
                    ->where('student_id', $current_user_id);

                $exercises = $exercises
                    ->whereNotIn('id', $exercises_ids_in_progress);

                $private_exercises = DB::table('Exercise')
                    ->join('ExerciseStudentPermissions', 'Exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->selectRaw('id, title, 0 as progress')
                    ->whereNotIn('id', $exercises_ids_in_progress)
                    ->where('isPrivate', true)
                    ->where('student_id', $current_user_id);

                $exercises_in_progress = DB::table('Exercise')
                        ->join('ExerciseStudent', 'Exercise.id', '=', 'ExerciseStudent.exercise_id')
                        ->select('id', 'title', 'progress')
                        ->where('student_id', $current_user_id);

                $exercises = $exercises->union($private_exercises);
                $exercises = $exercises->union($exercises_in_progress);
            }

            $exercises = $exercises->orderBy('id', 'asc')->get();
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return response()->json(['response_code' => 2], 200);
        } //@codeCoverageIgnoreEnd

        return response()->json(['response_code' => 0, 'exercises' => $exercises], 200);
    }

    /**
     * This function will get the exercise info from db and send it to the client.
     *
     * @param $id the id of the exercise of which the details will be sent
     *
     * @return the exercise details
     */
    public function getExerciseDetails($id)
    {
        try
        {
            $exercise = DB::table('Exercise')
                ->join('users', 'Exercise.creator_id', '=', 'users.id')
                ->selectRaw(
                    '"Exercise".title,
                     "Exercise".description,
                     "Exercise".image_path as image_base64,
                     users.name as creator_name,
                     0 as progress,
                     convert_from(\'\'::bytea, \'UTF8\') as feup8_file'
                )
                ->where('isPrivate', false)
                ->where('Exercise.id', '=', $id);

            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 != $current_user_id)
            { //logged in
                $exercise_ids_in_progress = DB::table('ExerciseStudent')
                    ->select('exercise_id as id')
                    ->where('student_id', $current_user_id)
                    ->where('exercise_id', '=', $id);

                $exercise = $exercise
                    ->whereNotIn('Exercise.id', $exercise_ids_in_progress);

                $private_exercise = DB::table('Exercise')
                    ->join('ExerciseStudentPermissions', 'Exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->join('users', 'Exercise.creator_id', '=', 'users.id')
                    ->selectRaw(
                        '"Exercise".title,
                        "Exercise".description,
                        "Exercise".image_path as image_base64,
                        users.name as creator_name,
                        0 as progress,
                        convert_from(\'\'::bytea, \'UTF8\')  as feup8_file'
                    )
                    ->whereNotIn('Exercise.id', $exercise_ids_in_progress)
                    ->where('isPrivate', true)
                    ->where('student_id', $current_user_id)
                    ->where('Exercise.id', '=', $id);

                $exercise_in_progress = DB::table('Exercise')
                        ->join('ExerciseStudent', 'Exercise.id', '=', 'ExerciseStudent.exercise_id')
                        ->join('users', 'Exercise.creator_id', '=', 'users.id')
                        ->selectRaw(
                            '"Exercise".title,
                            "Exercise".description,
                            "Exercise".image_path as image_base64,
                            users.name as creator_name,
                            progress,
                            convert_from(feup8_file::bytea, \'UTF8\') as feup8_file'
                        )
                        ->where('student_id', $current_user_id)
                        ->where('Exercise.id', '=', $id);

                $exercise = $exercise->union($private_exercise);
                $exercise = $exercise->union($exercise_in_progress);
            }

            $exercise = $exercise->get();

            if (0 == count($exercise))
            {
                return response()->json(['response_code' => 1], 200);
            }

            $tests = DB::table('Test')
                ->select('id', 'title', 'test_code', 'hint')
                ->where('exercise_id', '=', $id)
                ->get()
                ->toArray();
            //encode test_code of tests
            for ($i = 0; $i < count($tests); ++$i)
            {
                $tests[$i]->test_code = base64_encode($tests[$i]->test_code);
            }
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return response()->json(['response_code' => 2], 200);
        } //@codeCoverageIgnoreEnd

        return response()->json(['response_code' => 0, 'exercise' => $exercise, 'tests' => $tests], 200);
    }

    /**
     * This function will save the exercise progress of a student.
     *
     * @param $request the received request with the exercise data, the tic file of the development
     * @param $exercise_id the id of the exercise of which progress will be saved
     *
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
     */
    public function saveExerciseProgress(Request $request, $exercise_id)
    {
        $validator = Validator::make($request->all(), [
            'code' => 'required',
            'exercise_data' => 'required',
        ]);
        if ($validator->fails())
        {
            return response()->json(['response_code' => 2], 200);
        }

        if (!Auth::guard('api')->check())
        {
            return response()->json(['response_code' => 1], 200);
        }

        $progress = $this->getExerciseResolutionProgressBasedOnStudentCode($exercise_id, $request['code']);
        if (-1 == $progress)
        {
            return response()->json(['response_code' => 1], 200);
        } //@codeCoverageIgnoreStart
        elseif (-2 == $progress)
        {
            return response()->json(['response_code' => 2], 200);
        } //@codeCoverageIgnoreEnd

        try
        {
            if (ExerciseController::checkExerciseStudentExists($exercise_id, Auth::guard('api')->user()->id))
            {
                DB::table('ExerciseStudent')
                    ->where('exercise_id', '=', $exercise_id)
                    ->where('student_id', '=', Auth::guard('api')->user()->id)
                    ->update(['progress' => $progress, 'feup8_file' => $request['exercise_data']]);
            }
            else
            {
                DB::table('ExerciseStudent')->insert(['exercise_id' => $exercise_id, 'student_id' => Auth::guard('api')->user()->id,
                    'progress' => $progress, 'feup8_file' => $request['exercise_data'], ]);
            }
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return response()->json(['response_code' => 2], 200);
        } //@codeCoverageIgnoreEnd

        return response()->json(['response_code' => 0], 200);
    }

    /**
     * This function will retrieve the current progress of the exercise resolution based on student code.
     * It will run the tests for the exercise and the progress is equal to the quotient between the number of tests passing and the total number of tests.
     *
     * @param $exercise_id The id of the exercise which student is trying to solve
     * @param $code The student code for solving the exercise
     *
     * @return $progress The exercise resolution progress based on student code. -1 for perission denied. -2 for server error.
     */
    public function getExerciseResolutionProgressBasedOnStudentCode($exercise_id, $code)
    {
        $logged_user_id = 0;
        if (Auth::guard('api')->check())
        {
            $logged_user_id = Auth::guard('api')->user()->id;
        }

        $exercise_exists = DB::table('Exercise')
        ->select('id')
        ->where('id', $exercise_id)
        ->get()
        ->toArray();

        $unit_tests_code_array = DB::table('Test')
        ->select('Test.test_code')
        ->where('exercise_id', $exercise_id)
        ->get()
        ->toArray();

        if (0 == count($exercise_exists))
        {
            return -1;
        }

        if (0 == count($unit_tests_code_array))
        {
            return 0;
        }

        $unit_tests_code_array = $this->getExerciseTestsTestCode($exercise_id, $logged_user_id);
        //@codeCoverageIgnoreStart
        if (-1 === $unit_tests_code_array)
        {
            return -2;
        }
        //@codeCoverageIgnoreEnd
        $numberOfUnitTests = count($unit_tests_code_array);
        if (0 == $numberOfUnitTests)
        {
            return -1;
        }

        $decoded_code = base64_decode($code);
        $unit_tests_code_array = array_column(json_decode(json_encode($unit_tests_code_array)), 'test_code');
        $response = $this->testExerciseCodeUsingLuaUnitExecutor($decoded_code, $unit_tests_code_array);
        $progress = 0;
        if ($response[0] >= 0)
        { // number of tests that failed
            $progress = (($numberOfUnitTests - $response[0]) / $numberOfUnitTests) * 100;
        }

        return $progress;
    }

    /**
     * This function will check if an entry on database for ExerciseStudent with the auth user id and the exercise id given.
     *
     * @param exercise_id The id of the exercise to be checked
     *
     * @return bool true if exists, false otherwise
     */
    public static function checkExerciseStudentExists($exercise_id, $logged_user_id)
    {
        try
        {
            $exercise_student = DB::table('ExerciseStudent')
                ->select('*')
                ->where('exercise_id', '=', $exercise_id)
                ->where('student_id', '=', $logged_user_id)
                ->get();
            if (0 != count($exercise_student))
            {
                return true;
            }
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return true;
        } //@codeCoverageIgnoreEnd

        return false;
    }

    /**
     * This function will retrieve the test of an exercise existents in the database.
     *
     * @param $exercise_id the id of the exercise of which tests will be retrieved
     *
     * @return the retrieved list of tests, -1 otherwise
     */
    public function getExerciseTestsTestCode($exercise_id, $logged_user_id)
    {
        try
        {
            $public_exercise = DB::table('Exercise')
                ->select('id')
                ->where('Exercise.id', '=', $exercise_id)
                ->where('isPrivate', false);

            $possible_exercise = $public_exercise;

            if (0 != $logged_user_id)
            {
                $private_exercise = DB::table('Exercise')
                    ->join('ExerciseStudentPermissions', 'Exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->select('id')
                    ->where('Exercise.id', '=', $exercise_id)
                    ->where('isPrivate', true)
                    ->where('ExerciseStudentPermissions.student_id', $logged_user_id);

                $possible_exercise = $possible_exercise->union($private_exercise);
            }

            $unit_tests_code_array = DB::table('Test')
                ->select('Test.test_code')
                ->whereIn('exercise_id', $possible_exercise)
                ->get()
                ->toArray();

            return $unit_tests_code_array;
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return -1;
        } //@codeCoverageIgnoreEnd
    }

    /**
     * This function will test the code of a student using the tests of the respective exercise.
     *
     * @param $code the student code for the exercise
     * @param $unit_tests_code_array the list of unit tests for the exercise
     *
     * @return Possible return values:
     *                  [-2, "Execution timed out before finishing"] - execution timed out, possibly due to an infinite cycle in student code.
     *                  [-1, "Student code has one or more syntactic errors"] - syntactic error(s) on student code.
     *                  [0, "<luaunit output>"] - all tests passed. The string should be parsed with the LuaUnitParser.
     *                  [<value higher than 0>, "<luaunit output>"] - at least one test failed. The string should be parsed with the LuaUnitParser.
     */
    public function testExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array)
    {
        $luaUnitExecutor = new LuaUnitExecutor($code, $unit_tests_code_array);

        return $luaUnitExecutor->run();
    }

    /**
     * This function will test the code of a student using the tests of the respective exercise.
     *
     * @param $request the received request with the exercise code
     * @param $exercise_id the id of the exercise of which student code will be tested
     *
     * @return the response code 0 indicating sucess. Response code 1 indicating that code paramater must be in the request. Response code 2 for other errors.
     */
    public function handleTestStudentCode(Request $request, $exercise_id)
    {
        $validator = Validator::make($request->all(), [
            'code' => 'required',
        ]);
        if ($validator->fails())
        {
            return response()->json(['response_code' => 2], 200);
        }

        $logged_user_id = 0;
        if (Auth::guard('api')->check())
        {
            $logged_user_id = Auth::guard('api')->user()->id;
        }

        $unit_tests_code_array = $this->getExerciseTestsTestCode($exercise_id, $logged_user_id);
        if (-1 === $unit_tests_code_array)
        {
            //@codeCoverageIgnoreStart
            return response()->json(['response_code' => 2], 200);
            //@codeCoverageIgnoreEnd
        }
        if (0 == count($unit_tests_code_array))
        {
            return response()->json(['response_code' => 1], 200);
        }

        $decoded_code = base64_decode($request['code']);
        $unit_tests_code_array = array_column(json_decode(json_encode($unit_tests_code_array)), 'test_code');
        $response = $this->testExerciseCodeUsingLuaUnitExecutor($decoded_code, $unit_tests_code_array);
        if (-1 == $response[0] || -2 == $response[0])
        {
            return response()->json(['response_code' => 0, 'tests_global_state' => $response[0]], 200);
        }

        $lua_unit_parser = new LuaUnitParser();
        $tests_results = $lua_unit_parser->parse(implode("\n", $response[1]));

        return response()->json(['response_code' => 0, 'tests_global_state' => $response[0], 'tests_results' => json_decode($tests_results)], 200);
    }
}

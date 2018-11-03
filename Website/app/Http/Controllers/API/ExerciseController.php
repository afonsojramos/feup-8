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
     * @return A list of all available exercises in JSON, and the response code of 0 menig sucess. Response code 1 otherwise. 
     */ 
    public function getAllExercises()
    {
        try 
        {
            $exercises = DB::table('exercise')
                ->select('id', 'title', '0 as progress')
                ->where('isPrivate', false);

            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if ($current_user_id != 0) //logged in
            {
                $exercises_ids_in_progress = DB::table('ExerciseStudent')
                    ->select('exercise_id as id')
                    ->where('student_id', $current_user_id);

                $exercises = $exercises
                    ->whereNotIn('id', $exercises_ids_in_progress);

                $private_exercises = DB::table('exercise')
                    ->join('ExerciseStudentPermissions', 'exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->select('id', 'title', '0 as progress')
                    ->whereNotIn('id', $exercises_ids_in_progress)
                    ->where('isPrivate', true)
                    ->where('student_id', $current_user_id);
                

                $exercises_in_progress = DB::table('exercise')
                        ->join('ExerciseStudent', 'exercise.id', '=', 'ExerciseStudent.exercise_id')
                        ->select('id', 'title', 'progress')
                        ->where('student_id', $current_user_id);
                        
                $exercises = $exercises->union($private_exercises);
                $exercises = $exercises->union($exercises_in_progress);
            }

            $exercises = $exercises->get();
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>2], 200);
        }

        return response()->json(['response_code'=>0, 'exercises'=> $exercises], 200);
    }


    /** 
     * This function will get the exercise info from db and send it to the client.
     * @param $id The id of the exercise of which the details will be sent.
     * @return the exercise details
    */ 
    public function getExerciseDetails($id)
    { 
        try 
        {
            $exercise = DB::table('exercise')
                ->join('users', 'exercise.creator_id', '=', 'users.id')
                ->select('exercise.title', 'exercise.description', 'exercise.image_path as image_base64',
                'users.name as creator_name', '0 as progress', ' as feup8_file')
                ->where('isPrivate', false)
                ->where('exercise.id', '=', $id);
            
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if ($current_user_id != 0) //logged in
            {
                $exercise_ids_in_progress = DB::table('ExerciseStudent')
                    ->select('exercise_id as id')
                    ->where('student_id', $current_user_id)
                    ->where('exercise.id', '=', $id);

                $exercise = $exercise
                    ->whereNotIn('exercise.id', $exercise_ids_in_progress);

                $private_exercise = DB::table('exercise')
                    ->join('ExerciseStudentPermissions', 'exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->join('users', 'exercise.creator_id', '=', 'users.id')
                    ->select('exercise.title', 'exercise.description', 'exercise.image_path as image_base64',
                    'users.name as creator_name', '0 as progress', ' as feup8_file')
                    ->whereNotIn('exercise.id', $exercise_ids_in_progress)
                    ->where('isPrivate', true)
                    ->where('student_id', $current_user_id)
                    ->where('exercise.id', '=', $id);

                $exercise_in_progress = DB::table('exercise')
                        ->join('ExerciseStudent', 'exercise.id', '=', 'ExerciseStudent.exercise_id')
                        ->join('users', 'exercise.creator_id', '=', 'users.id')
                        ->select('exercise.title', 'exercise.description', 'exercise.image_path as image_base64',
                        'users.name as creator_name', 'progress', 'feup8_file')
                        ->where('student_id', $current_user_id)
                        ->where('exercise.id', '=', $id);
                        
                $exercise = $exercise->union($private_exercise);
                $exercise = $exercise->union($exercise_in_progress);
            }

            $exercise = $exercise->get();

            if (count($exercise) == 0)
                return response()->json(['response_code'=>1], 200);

            $tests = DB::table('test')
                ->select('id', 'title', 'test_code', 'hint')
                ->where('exercise_id', '=', $id)
                ->get()
                ->toArray();
            //encode test_code of tests
            for ($i = 0; $i < count($tests); $i++)
                $tests[$i]->test_code = base64_encode($tests[$i]->test_code);
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>2], 200);
        }

        return response()->json(['response_code'=>0, 'exercise'=> $exercise, 'tests' => $tests], 200);
    }

    /** 
     * This function will save the exercise progress of a student.
     * @param $request The received request with the exercise data, the tic file of the development.
     * @param $exercise_id The id of the exercise of which progress will be saved.
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
    */ 
    public function saveExerciseProgress(Request $request, $exercise_id)
    { 
        $validator = Validator::make($request->all(), [ 
            'code' => 'required',
            'exercise_data' => 'required', 
        ]);
        if ($validator->fails()) 
            return response()->json(['response_code'=>1], 200);   

        if(!Auth::guard('api')->check())
            return response()->json(['responde_code'=>1], 200); //must be logged in to save progress

        $progress = $this->getExerciseResolutionProgressBasedOnStudentCode($exercise_id, $request['code']);
        if($progress == -1)
            return response()->json(['response_code'=>1], 200);
        else if($progress == -2)
            return response()->json(['response_code'=>2], 200);
            
        try 
        {
            if(ExerciseController::checkExerciseStudentExists($exercise_id, Auth::guard('api')->user()->id))
            {
                DB::table('exerciseStudent')
                    ->where('exercise_id', '=', $exercise_id)
                    ->where('student_id', '=', Auth::guard('api')->user()->id)
                    ->update(['progress'=>$progress, 'feup8_file'=>$request['exercise_data']]);
            }
            else
            {
                DB::table('exerciseStudent')->insert(['exercise_id' => $exercise_id, 'student_id' => Auth::guard('api')->user()->id, 
                    'progress'=>$progress, 'feup8_file'=>$request['exercise_data']]);
            }    
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>2], 200);
        }

        return response()->json(['response_code'=>0], 200);
    }

    /** 
     * This function will retrieve the current progress of the exercise resolution based on student code. 
     * It will run the tests for the exercise and the progress is equal to the quotient between the number of tests passing and the total number of tests.
     * @param $exercise_id The id of the exercise which student is trying to solve
     * @param $code The student code for solving the exercise
     * @return $progress The exercise resolution progress based on student code. -1 for perission denied. -2 for server error.
    */ 
    public function getExerciseResolutionProgressBasedOnStudentCode($exercise_id, $code)
    { 
        $logged_user_id = 0;
        if(Auth::guard('api')->check())
            $logged_user_id = Auth::guard('api')->user()->id;

        $unit_tests_code_array = $this->getExerciseTests($exercise_id, $logged_user_id);
        if($unit_tests_code_array === -1)
            return -2;
        $numberOfUnitTests = count($unit_tests_code_array);
        if($numberOfUnitTests == 0)
            return -1;

        $decoded_code = base64_decode($code);
        $unit_tests_code_array = array_column(json_decode(json_encode($unit_tests_code_array)), 'test_code');
        $response = $this->testExerciseCodeUsingLuaUnitExecutor($decoded_code, $unit_tests_code_array);
        $progress = 0;
        if($response[0] >= 0) // number of tests that failed
            $progress = (($numberOfUnitTests - $response[0]) / $numberOfUnitTests) * 100;
        
        return $progress;
    }

    /** 
     * This function will check if an entry on database for ExerciseStudent with the auth user id and the exercise id given.     
     * @param exercise_id The id of the exercise to be checked
     * @return bool true if exists, false otherwise
    */ 
    public static function checkExerciseStudentExists($exercise_id, $logged_user_id)
    { 
        try 
        {
            $exercise_student = DB::table('exerciseStudent')
                ->select('*')
                ->where('exercise_id', '=', $exercise_id)
                ->where('student_id', '=', $logged_user_id)
                ->get();
            if(count($exercise_student) != 0)
                return true;
        } 
        catch (\Exception $e) 
        {
            return true;
        }

        return false;
    }

     /** 
     * This function will retrieve the test of an exercise existents in the database.
     * @param $exercise_id The id of the exercise of which tests will be retrieved.
     * @return the retrieved list of tests, -1 otherwise.
    */ 
    public function getExerciseTests($exercise_id, $logged_user_id)
    { 
        try
        {
            $public_exercise = DB::table('exercise')
                ->select('id')
                ->where('exercise.id', '=', $exercise_id)
                ->where('isPrivate', false);

            $possible_exercise = $public_exercise;

            if($logged_user_id != 0)
            {
                $private_exercise = DB::table('exercise')
                    ->join('ExerciseStudentPermissions', 'exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->select('id')
                    ->where('exercise.id', '=', $exercise_id)
                    ->where('isPrivate', true)
                    ->where('ExerciseStudentPermissions.student_id', $logged_user_id);

                $possible_exercise = $possible_exercise->union($private_exercise);   
            }
                
            $unit_tests_code_array = DB::table('test')
                ->select('test.test_code')
                ->whereIn('exercise_id', $possible_exercise)
                ->get();
            
            return $unit_tests_code_array;
        }
        catch (\Exception $e) 
        {
            return -1;
        }
    }

     /** 
     * This function will test the code of a student using the tests of the respective exercise.
     * @param $code The student code for the exercise.
     * @param $unit_tests_code_array The list of unit tests for the exercise.
     * @return Possible return values:
     * [-2, "Execution timed out before finishing"] - execution timed out, possibly due to an infinite cycle in student code.
     * [-1, "Student code has one or more syntactic errors"] - syntactic error(s) on student code.
     * [0, "<luaunit output>"] - all tests passed. The string should be parsed with the LuaUnitParser.
     * [<value higher than 0>, "<luaunit output>"] - at least one test failed. The string should be parsed with the LuaUnitParser.
    */ 
    public function testExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array)
    { 
        $luaUnitExecutor = new LuaUnitExecutor($code, $unit_tests_code_array);
        return $luaUnitExecutor->run();
    }

     /** 
     * This function will test the code of a student using the tests of the respective exercise.
     * @param $request The received request with the exercise code.
     * @param $exercise_id The id of the exercise of which student code will be tested.
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
    */ 
    public function handleTestStudentCode(Request $request, $exercise_id)
    { 
        $validator = Validator::make($request->all(), [ 
            'code' => 'required',
        ]);
        if ($validator->fails()) 
            return response()->json(['response_code'=>1], 200); 

        $logged_user_id = 0;
        if(Auth::guard('api')->check())
            $logged_user_id = Auth::guard('api')->user()->id;

        $unit_tests_code_array = $this->getExerciseTests($exercise_id, $logged_user_id);
        if($unit_tests_code_array === -1)
            return response()->json(['response_code'=>2], 200);
        if(count($unit_tests_code_array) == 0)
            return response()->json(['response_code'=>1], 200);

        $decoded_code = base64_decode($request['code']);
        $unit_tests_code_array = array_column(json_decode(json_encode($unit_tests_code_array)), 'test_code');
        $response = $this->testExerciseCodeUsingLuaUnitExecutor($decoded_code, $unit_tests_code_array);
        if($response[0] == -1 || $response[0] == -2)
            return response()->json(['response_code'=>0, 'tests_global_state'=>$response[0]], 200);
        
        $lua_unit_parser = new LuaUnitParser();
        $tests_results =  $lua_unit_parser->parse(implode("\n", $response[1]));
        return response()->json(['response_code'=>0, 'tests_global_state'=>$response[0], 'tests_results'=>json_decode($tests_results)], 200);
    }

}
<?php

namespace App\Http\Controllers\API;

use Illuminate\Http\Request; 
use App\Http\Controllers\Controller; 
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
                ->get();
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
        if(!Auth::guard('api')->check())
            return response()->json(['responde_code'=>1], 200); //must be logged in to save progress

        // TODO: $progress = correr a funçao que vai executar os testes para saber o progress, $request['code']
        $progress = 10;
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
     * This function will check if an entry on database for ExerciseStudent with the auth user id and the exercise id given.     
     * @param exercise_id The id of the exercise to be checked
     * @return bool true if exists, false otherwise
    */ 
    public static function checkExerciseStudentExists($exercise_id, $user_id)
    { 
        try 
        {
            $exercise_student = DB::table('exerciseStudent')
                ->select('*')
                ->where('exercise_id', '=', $exercise_id)
                ->where('student_id', '=',  $user_id)
                ->get();
            if(count($exercise_student) != 0)
                return true;
        } 
        catch (\Exception $e) 
        {
            return false;
        }

        return false;
    }


     /** 
     * This function will test the code of a student using the tests of the respective exercise.
     * @param $request The received request with the exercise code.
     * @param $exercise_id The id of the exercise of which student code will be tested.
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
    */ 
    public function testStudentCodeForExercise(Request $request, $exercise_id)
    { 
        $tests_results_array = array
        (
            array("id"=>"1", "result"=>"OK")
        );
        return response()->json(['response_code'=>0, 'tests_results'=>$tests_results_array], 200);
        
        try
        {
            $public_exercise = DB::table('exercise')
            ->select('id')
            ->where('exercise.id', '=', $exercise_id)
            ->where('isPrivate', false);

            $possible_exercise = $public_exercise;

            if(Auth::guard('api')->check())
            {
                $userID = Auth::guard('api')->user()->id;

                $private_exercise = DB::table('exercise')
                    ->join('ExerciseStudentPermissions', 'exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->select('id')
                    ->where('exercise.id', '=', $exercise_id)
                    ->where('isPrivate', true)
                    ->where('ExerciseStudentPermissions.student_id', $userID);

                $possible_exercise = $possible_exercise->union($private_exercise);
                
            }
                
            $tests_code_array = DB::table('test')
                ->select('test.test_code')
                ->whereIn('exercise_id', $possible_exercise)
                ->get();
        }
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>2], 200);
        }
       
        if(count($tests_code_array) == 0)
            return response()->json(['response_code'=>1], 200);

        //TODO: $tests_results_array = funcTiago($request['code'], $tests_code_array);
        //TODO: return response()->json(['response_code'=>0, 'tests_results'=>$tests_results_array], 200);
    }

}
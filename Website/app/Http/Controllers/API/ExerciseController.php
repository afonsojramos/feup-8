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
        /*TODO: send also the progress if logged in
            ->join('ExerciseStudent', 'exercise.id', '=', 'ExerciseStudent.exercise_id')
            ->select('id', 'title', 'progress')
            e fazer para non private*/
        try 
        {
            $exercises = DB::table('exercise')
                ->select('id', 'title', '0 as progress')
                ->where('isPrivate', 'false');

            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if ($current_user_id != 0) //logged in
            {
                $private_exercises = DB::table('exercise')
                    ->join('ExerciseStudentPermissions', 'exercise.id', '=', 'ExerciseStudentPermissions.exercise_id')
                    ->select('id', 'title', '0 as progress')
                    ->where('isPrivate', 'true')
                    ->where('student_id', $current_user_id);
                
                $exercises_in_progress = DB::table('exercise')
                    ->join('ExerciseStudent', 'exercise.id', '=', 'ExerciseStudent.exercise_id')
                    ->select('id', 'title', 'progress')
                    ->where('student_id', 1);
                
                $exercises = $exercises_in_progress->union($exercises)->distinct('exercise.id');
                $exercises = $exercises->union($private_exercises)->distinct('exercise.id');
                //$exercises = $exercises_in_progress;
            }

            $exercises = $exercises->get();
            
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>1], 200);
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
        //TODO: verify id por permissoes para ver o exercise
        try 
        {
            $exercise = DB::table('exercise')
                ->join('test', 'exercise.id', '=', 'test.exercise_id')
                ->join('users', 'exercise.creator_id', '=', 'users.id')
                ->select('exercise.title', 'exercise.description', 'exercise.image_path as image_base64',
                    'test.tests_code as test_code_base64', 'users.name as creator_name')
                ->where('isPrivate', 'false')
                ->where('exercise.id', '=', $id);

            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            
            if ($current_user_id != 0) //logged in
            {
                $private_exercise = DB::table('exercise')
                ->join('test', 'exercise.id', '=', 'test.exercise_id')
                ->join('users', 'exercise.creator_id', '=', 'users.id')
                ->select('exercise.title', 'exercise.description', 'exercise.image_path as image_base64',
                    'test.tests_code as test_code_base64', 'users.name as creator_name')
                ->where('isPrivate', 'true')
                ->where('student_id', $current_user_id)
                ->where('exercise.id', '=', $id);

                $exercise = $exercise->unionAll($private_exercise);
            }

            $exercise = $exercise->distinct('exercise.id')->get();

            //TODO: send feup8 file
            //TODO: send image then
            //TODO: ->join('exerciseStudent', 'exercise.id', '=', 'exerciseStudent.exercise_id') mas com exerciseStudent.student_id = Auth::id indo buscar o 'exerciseStudent.progress' no select
        } 
        catch (\Exception $e) 
        {
            return $e;
            return response()->json(['response_code'=>1], 200);
        }

        return response()->json(['response_code'=>0, 'exercise'=> $exercise], 200);
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

        // $progress = correr a funçao que vai executar os testes para saber o progress, $request['code']
        try 
        {
            if(checkExerciseStudentExists())
            {
                DB::table('exerciseStudent')
                    ->where('exercise_id', '=', $exercise_id)
                    ->where('student_id', '=', Auth::user()->id)
                    ->update(['progress'=>$progress])
                    ->update(['feup8_file'=>$request['exercise_data']]);
            }
            else
            {
                DB::table('exerciseStudent')->insert(['exercise_id' => $exercise_id, 'student_id' => Auth::user()->id, 
                    'progress'=>$progress, 'feup8_file'=>$request['exercise_data']]);
            }    
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>1], 200);
        }

        return response()->json(['response_code'=>0], 200);
    }


    /** 
     * This function will check if an entry on database for ExerciseStudent with the auth user id and the exercise id given.     
     * @param exercise_id The id of the exercise to be checked
     * @return bool true if exists, false otherwise
    */ 
    public static function checkExerciseStudentExists($exercise_id)
    { 
        try 
        {
            $exercise_student = DB::table('exerciseStudent')
                ->select('*')
                ->where('exercise_id', '=', $exercise_id)
                ->where('student_id', '=', Auth::id)
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
     * This function will save the exercise progress of a student.
     * @param $request The received request with the exercise code.
     * @param $exercise_id The id of the exercise of which student code will be tested.
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
    */ 
    public function testStudentCodeForExercise(Request $request, $exercise_id)
    { 
       
    }

}
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
        //TODO: add exercises that are private but that user has access
        //TODO: send also the progress if logged in
        try 
        {
            $exercises = DB::table('exercise')->select('id', 'title')->where('isPrivate', 'false')->get();
            return response()->json(['response_code'=>0, 'exercises'=> $exercises], 200);
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>1], 200);
        }
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
                 'test.correct_code as correct_code_base64' , 'test.tests_code as test_code_base64', 'users.name as creator_name')
            ->where('exercise.id', '=', $id)->get();
            //TODO: send image then
            //TODO: ->join('exerciseStudent', 'exercise.id', '=', 'exerciseStudent.exercise_id') mas com exerciseStudent.student_id = Auth::id indo buscar o 'exerciseStudent.progress' no select
            return response()->json(['response_code'=>0, 'exercise'=> $exercise], 200);
        } 
        catch (\Exception $e) 
        {
            return response()->json(['response_code'=>1], 200);
        }
    }

    /** 
     * This function will save the exercise progress of a student.
     * @param $id The id of the exercise of which progress will be saved.
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged in to save progress. Response code 2 for other errors.
    */ 
    public function saveExerciseProgress(Request $request, $id)
    { 
        if(!Auth::check())
            return response()->json(['responde_code'=>1], 200); //must be logged in to save progress

        
    }

}
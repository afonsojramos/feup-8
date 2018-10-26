<?php

use Illuminate\Http\Request;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/

//TODO remove---isto vem originalmente no laravel
/*Route::middleware('auth:api')->get('/user', function (Request $request) {
    return $request->user();*/

//User management
Route::post('login', 'API\UserController@login');
Route::post('register', 'API\UserController@register');
Route::post('logout', 'API\UserController@logout');


//Exercises management
Route::get('exercises/all', 'API\ExerciseController@getAllExercises');
Route::get('exercises/{exercise_id}', 'API\ExerciseController@getExerciseDetails');
Route::post('exercises/{exercise_id}/save', 'API\ExerciseController@saveExerciseProgress');
Route::get('exercises/{exercise_id}/test', 'API\ExerciseController@testStudentCodeForExercise');
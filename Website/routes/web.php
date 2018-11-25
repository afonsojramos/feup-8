<?php

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function ()
{
    return view('welcome');
});

Auth::routes();

Route::get('/home', 'HomeController@index')->name('home');
Route::get('/exercise/create', 'Web\ExerciseController@createExercisePage');
Route::post('/exercise/create', 'Web\ExerciseController@createExercise')->name('/exercise/create');
Route::post('/login', 'Web\UserController@login');
Route::post('/register', 'Web\UserController@register');
Route::get('/exercises', 'Web\ExerciseController@getAllExercises');
Route::get('/teacher/exercises', 'Web\ExerciseController@getAllExercisesFromUser');

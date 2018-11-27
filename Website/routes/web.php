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

Route::get('/', 'HomeController@start');

Auth::routes();

Route::post('/login', 'Web\UserController@login');
Route::post('/register', 'Web\UserController@register');

Route::get('/home', 'HomeController@index')->name('home');

Route::get('/exercise/create', 'Web\ExerciseController@createExercisePage');
Route::post('/exercise/create', 'Web\ExerciseController@createExercise')->name('/exercise/create');
Route::get('/exercise/{id}', 'Web\ExerciseController@viewExercisePage');
Route::post('/exercise/{id}/edit', 'Web\ExerciseController@editExercise');
Route::post('/exercise/{id}/addTest', 'Web\TestController@addTestToExercise');
Route::post('/exercise/{id}/edit/test/{test_id}/remove', 'Web\TestController@removeTest');
Route::post('/exercise/{id}/edit/test/{test_id}/', 'Web\TestController@editTestCode');
Route::post('/exercise/{id}/edit/test/{test_id}/tip', 'Web\TestController@addTipToExercise');

Route::get('/exercises', 'Web\ExerciseController@getAllExercises');

Route::get('/teacher/exercises', 'Web\ExerciseController@getAllExercisesFromUser');

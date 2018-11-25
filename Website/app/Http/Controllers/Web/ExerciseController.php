<?php

namespace App\Http\Controllers\Web;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\User;
use Validator;
use DB;

class ExerciseController extends Controller
{
    public function getAllExercises()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        $exercises = DB::select('SELECT * FROM exercise');

        foreach ($exercises as $exercise)
        {
            $exercise->creator_name = User::find($exercise->creator_id)->name;
        }

        return view('exercise.exercises', ['exercises' => $exercises]);
    }

    public function getAllExercisesFromUser()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        if (0 == $current_user_id)
        {
            return 'FORBIDDEN';
        }
        $exercises = DB::select('SELECT * FROM exercise where creator_id=?', [$current_user_id]);

        return view('teacher.exercises', ['exercises' => $exercises]);
    }

    /**
     * This function will create an exercise on a database.
     *
     * @param $request the received request with form data filled that contains the information to insert in the database
     *
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged as teacher in to create exercise. Response code 2 for other errors.
     */
    public function createExercisePage()
    {
        return view('exercise/create_exercise');
    }

    /**
     * This function will create an exercise on a database.
     *
     * @param $request the received request with form data filled that contains the information to insert in the database
     *
     * @return the response code 0 indicating sucess. Response code 1 indicating that must be logged as teacher in to create exercise. Response code 2 for other errors.
     */
    public function createExercise(Request $request)
    {
        $validator = Validator::make($request->all(), [
            'form-title' => 'required',
            'form-description' => 'required',
        ]);

        $username = $request->input('form-title');
        $description = $request->input('form-description');
        $isPrivate;
        if (isset($_POST['form-isPrivate']))
        {
            $isPrivate = true;
        }
        else
        {
            $isPrivate = false;
        }

        if ($validator->fails())
        {
            return redirect('/exercise/create')->withErrors(['msg' => 'Please fill all the fields.']);
        }

        try
        {
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 == $current_user_id)
            {
                return 'FORBIDDEN';
            }

            //Check if the user is a teacher (if not, he doesn't have permission to create an exercise)
            $teacher = DB::table('users')
                ->select('id')
                ->where('isTeacher', true)
                ->where('id', '=', $current_user_id)
                ->first();

            //This error messages are not "pretty" because if the user landed on this page without being logged in as teacher, he was not supposed to, so the previous page may not even have support to display error messages and he is probably trying to cheat permission system
            if (null == $teacher)
            {
                return 'FORBIDDEN';
            }

            DB::table('exercise')->insert([
                    ['title' => $username,
                    'description' => $description,
                    'creator_id' => $current_user_id,
                    'isPrivate' => $isPrivate,
                    'created_at' => now(),
                    'updated_at' => now(),
                    ],
                ]);
        }
        catch (\Exception $e)
        {
            if (23000 == $e->getCode())
            { //already exists an exercise with the same title
                return redirect('/exercise/create')->withErrors(['msg' => 'Sorry, there is already an exercise with that title. Please choose a different title.']);
            }
            else
            {
                return redirect('/exercise/create')->withErrors(['msg' => 'Sorry, there was an issue executing your request. If you believe this is an error, please contact system admin.']);
            }
        }

        return redirect('/exercise/create')->withErrors(['msg' => 'Exercise created successfully.']);
    }
}

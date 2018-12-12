<?php

namespace App\Http\Controllers\Web;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\User;
use Validator;
use DB;

class ExerciseController extends Controller
{
    /**
     * This function will return all the exercises on the database.
     *
     * @return the response the view of listing exercises with all the exercises as parameter
     */
    public function getAllExercises()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        $exercises = DB::table('Exercise')->SimplePaginate(5);

        foreach ($exercises as $exercise)
        {
            $exercise->creator_name = User::find($exercise->creator_id)->name;
        }

        return view('exercise.exercises', ['exercises' => $exercises]);
    }

    /**
     * This function will return all the exercises of an user on the database.
     *
     * @return the response the view of listing exercises of user/teacher
     *             with all the exercises as parameter. If the user is not loggedin returns abort(403, 'Unauthorized action.');
     */
    public function getAllExercisesFromUser()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        if (0 == $current_user_id)
        {
            return abort(403, 'Unauthorized action.');
        }

        $exercises = DB::table('Exercise')->where('creator_id', $current_user_id)->SimplePaginate(4);

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
                return abort(403, 'Unauthorized action.');
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
                return abort(403, 'Unauthorized action.');
            }

            $inserted_exercise_id = DB::table('Exercise')->insertGetId(
                array(
                    'title' => $username,
                    'description' => $description,
                    'creator_id' => $current_user_id,
                    'isPrivate' => $isPrivate,
                    'created_at' => now(),
                    'updated_at' => now(),
                ));

            DB::table('ExerciseStudentPermissions')->insert([
                ['student_id' => $current_user_id,
                'exercise_id' => $inserted_exercise_id,
                ], ]);
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

        return redirect('/exercise/create')->with(['msg' => 'Exercise created successfully.']);
    }

    /**
     * This function will delete an exercise from the database.
     *
     * @param $id the id of the exercise we want to delete from the database
     *
     * @return the exercise list view on success and "FORBIDDEN" on not loogedin or the authenticated user not being its creator
     */
    public function deleteExercise($id)
    {
        try
        {
            $current_user_id = UserController::getCurrentlyLoggedInUserId();
            if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
            {
                return abort(403, 'Unauthorized action.');
            }

            DB::table('Exercise')->where('id', $id)->delete();
        }
        catch (\Exception $e)
        {
            return redirect('/exercise/'.$id)->withErrors(['msg' => 'Sorry, there was an issue executing your request. If you believe this is an error, please contact system admin.']);
        }

        return redirect('exercises/');
    }

    /**
     * This function will fetch the informations of an exercise from the database.
     *
     * @param $id the id of the exercise we want to fetch information on from the database
     *
     * @return the exercise view on success and exercise list with msg 'Sorry, there was an issue executing your request. If
     *             you believe this is an error, please contact system admin.' on error.
     */
    public function viewExercisePage($id)
    {
        try
        {
            $exercise = DB::table('Exercise')->where('id', '=', $id)->first();
            $exercise->creator_name = User::find($exercise->creator_id)->name;
            $exercise->tests = DB::table('Test')->where('exercise_id', '=', $id)->orderBy('id', 'desc')->simplePaginate(1);

            return view('exercise/exercise_view', ['exercise' => $exercise]);
        } //@codeCoverageIgnoreStart
        catch (\Exception $e)
        {
            return redirect('/exercise/'.$id)->withErrors(['msg' => 'Sorry, there was an issue executing your request. If you believe this is an error, please contact system admin.']);
        } //@codeCoverageIgnoreEnd
    }

    /**
     * This function will update the description of an exercise from the database.
     *
     * @param $id the id of the exercise we want to update the description on from the database
     *
     * @return the exercise view on success, abort(403, 'Unauthorized action.'); on the authenticated user not being
     *             the creator of the exercise and exercise list with msg 'Sorry, there was an issue
     *             executing your request. If you believe this is an error, please contact system admin.' on error.
     */
    public function editExercise(Request $request, $id)
    {
        if ($request->has('form-description'))
        {
            try
            {
                $current_user_id = UserController::getCurrentlyLoggedInUserId();
                if (0 == $current_user_id || $current_user_id != DB::table('Exercise')->where('id', $id)->first()->creator_id)
                {
                    return abort(403, 'Unauthorized action.');
                }

                $exercise = DB::table('Exercise')->where('id', $id)->update(['description' => $request['form-description']]);
            } //@codeCoverageIgnoreStart
            catch (\Exception $e)
            {
                return redirect('/exercise/'.$id)->withErrors(['msg' => 'Sorry, there was an issue executing your request. If you believe this is an error, please contact system admin.']);
            } //@codeCoverageIgnoreEnd
        }

        return redirect('exercise/'.$id);
    }
}

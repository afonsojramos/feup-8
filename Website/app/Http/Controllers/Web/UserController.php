<?php

namespace App\Http\Controllers\Web;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use Redirect;
use DB;
use Auth;
use Validator;
use App\User;

class UserController extends Controller
{
    /**
     * Login a user to the system. It is used just in the website.
     *
     * @param \Illuminate\Http\Request $request
     *
     * @return \Illuminate\Http\Response redirect to the most adequated page
     */
    public function login(Request $request)
    {
        $validator = Validator::make($request->all(), [
            'username' => 'required',
            'password' => 'required',
        ]);
        if ($validator->fails())
        {
            return redirect('login')->withErrors(['msg' => 'Missing username or password']);
        }

        $credentials = $request->only('username', 'password');
        if (Auth::attempt($credentials))
        {
            $user = Auth::user();
            session()->put('user_id', $user->id);

            return redirect('/');
        }
        else
        {
            return redirect('login')->withErrors(['msg' => 'The username and password do not match']);
        }
    }

    /**
     * Allows to create a user (Teacher) in the db.
     *
     * @param \Illuminate\Http\Request $request
     *
     * @return \Illuminate\Http\Response redirect to the most adequated page
     */
    public function register(Request $request)
    {
        $validator = Validator::make($request->all(), [
            'name' => 'required',
            'username' => 'required',
            'email' => 'required',
            'password' => 'required',
            'password_confirmation' => 'required',
        ]);
        if ($validator->fails())
        {
            return redirect('register')->withErrors(['msg' => 'Missing one or more elements: name, username, email, password, password confirmation']);
        }

        $input = $request->all();
        if ($request['password'] != $request['password_confirmation'])
        {
            return redirect('register')->withErrors(['msg' => 'Password does not match confirmation password!']);
        }
        if (User::checkUserExists($input['username']))
        {
            return redirect('register')->withErrors(['msg' => 'Username already existent!']);
        }
        if (!User::create($input['username'], $input['password'], $input['name'], $input['email'], true))
        {
            return redirect('register')->withErrors(['msg' => 'Error creating your account!']);
        }

        $id = DB::table('users')->select('id')->where('username', '=', $request['username'])->get();

        return $this->login($request);
    }

    /**
     * Get Currently Logged in user.
     *
     * @return Id of Currently Logged in user or 0 on no authenticated user
     */
    public static function getCurrentlyLoggedInUserId()
    {
        if (Auth::check())
        {
            return Auth::user()->id;
        }
        else
        {
            return 0;
        }
    }
}

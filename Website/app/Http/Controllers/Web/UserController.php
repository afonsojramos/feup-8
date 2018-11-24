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
            return redirect('login')->withErrors(['msg' => "Username password doesn't exist"]);
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
            'username' => 'required',
            'name' => 'required',
            'password' => 'required',
            'email' => 'required',
        ]);
        if ($validator->fails())
        {
            return redirect('register')->with(['msg' => 'Missing one or more elements: username, name, password, email']);
        }

        $input = $request->all();
        if (User::checkUserExists($input['username']))
        {
            return redirect('register')->withErrors(['msg' => 'Username already existent!']);
        }
        if (!User::create($input['username'], $input['password'], $input['name'], $input['email'], true))
        {
            return redirect('register')->withErrors(['msg' => 'Error creating your account!']);
        }

        $id = DB::table('users')->select('id')->where('username', '=', $request['username'])->get();
        session()->put('user_id', $id[0]->id);

        return redirect('');
    }

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

    //Probably not needed, laravel already does it
     /*
     * Allows to do logout to a user.
     *
     * @return \Illuminate\Http\Response redirect to the most home page, not logged in.
     */
  /*  public function logout()
    {
        return 5;
        Auth::logout();
        return redirect('');
    }*/
}

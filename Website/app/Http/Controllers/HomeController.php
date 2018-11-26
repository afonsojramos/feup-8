<?php

namespace App\Http\Controllers;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        return view('home');
    }

    public function start()
    {
        $current_user_id = UserController::getCurrentlyLoggedInUserId();
        if (0 == $current_user_id)
        {
            return view('auth.login');
        }

        return redirect('/home');
    }
}

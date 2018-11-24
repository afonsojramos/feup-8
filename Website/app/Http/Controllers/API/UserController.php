<?php

namespace App\Http\Controllers\API;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\User;
use Illuminate\Support\Facades\Auth;
use Validator;

class UserController extends Controller
{
    public static $successStatus = 200;

    /**
     * This methods allows to login a user.
     * The username and password will be checked for existing in the database, and if match.
     *
     * @param $request the post request with the username and password data
     *
     * @return JSON response with response code (0-success, 1-username/password dont match)
     */
    public static function login(Request $request)
    {
        $credentials = $request->only('username', 'password');

        if (Auth::attempt($credentials))
        {
            $user = Auth::user();
            $response['response_code'] = 0;
            $response['auth_token'] = $user->createToken('MyApp')->accessToken;

            return response()->json($response, UserController::$successStatus);
        }
        else
        {
            return response()->json(['response_code' => 1], 200);
        }
    }

    /**
     * This methods allows to register a user in the database.
     * All request parameters (name, username, email and password) are required.
     *
     * @param $request the post request with the name, username, email and password data
     *
     * @return JSON response with response code (0-success, 1-username/password dont match, 2-server error)
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
            return response()->json(['response_code' => 1], 200);
        }

        $input = $request->all();
        if (User::checkUserExists($input['username']))
        {
            return response()->json(['response_code' => 1], UserController::$successStatus);
        }
        if (!User::create($input['username'], $input['password'], $input['name'], $input['email'], false))
        {
            return response()->json(['response_code' => 2], UserController::$successStatus);
        }

        return UserController::login($request);
    }

    /**
     * Logout's the user currently logged in.
     *
     * @return the response code (0 indicating sucess, 1 not logged in, 2 server error)
     */
    public function logout()
    {
        if (!Auth::guard('api')->check())
        { //not logged in
            return response()->json(['response_code' => 1], 200);
        }

        if (!Auth::guard('api')->user()->token()->revoke())
        {
            return response()->json(['response_code' => 2], 200);
        }

        return response()->json(['response_code' => 0], UserController::$successStatus);
    }

    /**
     * Get's  the current logged in user.
     *
     * @return the id of the logged in user, 0 if noone logged in
     */
    public static function getCurrentlyLoggedInUserId()
    {
        if (Auth::guard('api')->check())
        {
            return Auth::guard('api')->id();
        }
        else
        {
            return 0;
        }
    }
}

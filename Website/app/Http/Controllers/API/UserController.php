<?php

namespace App\Http\Controllers\API;

use Illuminate\Http\Request; 
use App\Http\Controllers\Controller; 
use App\User; 
use Illuminate\Support\Facades\Auth; 
use Validator;
use Hash;
use DB;

class UserController extends Controller 
{

    public $successStatus = 200;

    /** 
     * This methods allows to login a user. 
     * The username and password will be checked for existing in the database, and if match.
     * @param $request The post request with the username and password data.
     * @return JSON response with response code (0-success, 1-username/password dont match). 
    */  
    public function login(Request $request)
    { 
        $credentials = $request->only('username', 'password');

        if (Auth::attempt($credentials)) 
        {
            $user = Auth::user(); 
            $response['auth_token'] =  $user->createToken('MyApp')->accessToken; 
            $response['response_code'] =  0; 
            return response()->json($response, $this->successStatus); 
        }
        else
            return response()->json(['response_code'=> 1], 200);
    }
    
    /** 
     * This methods allows to register a user in the database. 
     * All request parameters (name, username, email and password) are required.
     * @param $request The post request with the name, username, email and password data.
     * @return JSON response with response code (0-success, 1-username/password dont match, 2-server error). 
    */ 
    public function register(Request $request) 
    { 
        //TODO: make user being logged in after register
        $validator = Validator::make($request->all(), [ 
            'username' => 'required',
            'name' => 'required', 
            'password' => 'required',
            'email' => 'required',
        ]);
        if ($validator->fails()) 
            return response()->json(['response_code'=>1], 200);            

        $input = $request->all(); 
        if(User::checkUserExists($input['username']))
            return response()->json(['response_code'=>1], $this->successStatus);
        if(!User::create($input['username'], $input['password'], $input['name'], $input['email']))
            return response()->json(['response_code'=>2], $this->successStatus); 

        return response()->json(['response_code'=>0], $this->successStatus);  
    }

    /** 
     * Logout's the user currently logged in.
     * @return the response code (0 indicating sucess, 1 not logged in, 2 server error)
    */ 
    public function logout() 
    {
        if (!Auth::guard('api')->check()) //not logged in
            return response()->json(['response_code' => 1], 200);

        if (!Auth::guard('api')->user()->token()->revoke())
            return response()->json(['response_code' => 2], 200);

        return response()->json(['response_code' => 0], $this->successStatus); 
    }

    /** 
     * Get's  the current logged in user.
     * @return the id of the logged in user, 0 if noone logged in.
    */
    public static function getCurrentlyLoggedInUserId()
    {
        if (Auth::guard('api')->check())
            return Auth::guard('api')->id();
        else
            return 0;
    }

}
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
     * login api 
     * 
     * @return \Illuminate\Http\Response 
     */ 
    public function login(Request $request)
    { 
        $username = $request->input('username');
        $password = $request->input('password');
        if (empty($username) || empty($password))
            return response()->json(['response_code'=> 1], 200);
        try 
        {
            $user = \App\User::where('username', $username)->first();
        } 
        catch (\Illuminate\Database\QueryException $e) 
        {
            return $e;
            return response()->json(['response_code'=> 1], 200);
        }
        if ($user == null)
            return response()->json(['response_code'=> 1], 200);
        else if ($user == "null")
            return response()->json(['response_code'=> 1], 200);
        
            if (Auth::attempt(['username' => $username, 'password' => $password])) {
                echo "The user is active, not suspended, and exists.";
            }

        $hashed_password = $user->password;
        if (Hash::check($password, $hashed_password)) 
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
     * The username will be checked for non existing yet, and both username and password asre requeired 
     * @param $request The post request with the username and password data.
     * @return JSON response with response code (0-success, 1-username/password dont match, 2-server error). 
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
            return response()->json(['response_code'=>1], 200);            
        }
        $input = $request->all(); 
        //return User::create($input['username'], $input['password'], $input['name'], $input['email']);
        //return  DB::table('users')->select('*')->where('username', '=', $input['username'])->get();
        if(User::checkUserExists($input['username']))
            return response()->json(['response_code'=>1], $this->successStatus);
        if(!User::create($input['username'], $input['password'], $input['name'], $input['email']))
        {
            return response()->json(['response_code'=>2], $this->successStatus); 
        }

        return response()->json(['response_code'=>0], $this->successStatus);  
    }


     /** 
     * Logout's the user currently logged in.
     * @return the response code 0 indicating sucess.
     */ 
    public function logout() 
    {
        if (Auth::check())
            Auth::logout();
        return response()->json(['auth_token'=>0], $this->successStatus); 
    }

}
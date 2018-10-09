<?php

namespace App\Http\Controllers\API;

use Illuminate\Http\Request; 
use App\Http\Controllers\Controller; 
use App\User; 
use Illuminate\Support\Facades\Auth; 
use Validator;

class UserController extends Controller 
{

    public $successStatus = 200;

    /** 
     * login api 
     * 
     * @return \Illuminate\Http\Response 
     */ 
    public function login()
    { 
        if(Auth::attempt(['username' => request('username'), 'password' => request('password')]))
        { 
            $user = Auth::user(); 
            $response['token'] =  $user->createToken('MyApp')-> accessToken; 
            $response['response_code'] =  0; 
            return response()->json($response, $this->successStatus); 
        } 
        else
        { 
            return response()->json(['response_code'=> 1], 200);  //response code 1 means username password don't matvh
        } 
    }
/** 
     * Register api 
     * 
     * @return \Illuminate\Http\Response 
     */ 
    public function register(Request $request) 
    { 
        $validator = Validator::make($request->all(), [ 
            'name' => 'required', 
            'email' => 'required|email', 
            'password' => 'required', 
            'c_password' => 'required|same:password', 
        ]);
        if ($validator->fails()) { 
                    return response()->json(['error'=>$validator->errors()], 401);            
                }
        $input = $request->all(); 
                $input['password'] = bcrypt($input['password']); 
                $user = User::create($input); 
                $success['token'] =  $user->createToken('MyApp')-> accessToken; 
                $success['name'] =  $user->name;
        return response()->json(['success'=>$success], $this-> successStatus); 
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
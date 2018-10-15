<?php

namespace App;

use Laravel\Passport\HasApiTokens;
use Illuminate\Notifications\Notifiable;
use Illuminate\Contracts\Auth\MustVerifyEmail;
use Illuminate\Foundation\Auth\User as Authenticatable;
use DB;

class User extends Authenticatable
{
    use HasApiTokens, Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name', 'email', 'password',
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password', 'remember_token',
    ];


     /** 
     * This function will create a user, student or teacher.
     * @param $username The username of the user to create
     * @param $password The password for the user
     * @return the response code 0 indicating sucess. Response code 1 indicating failure otherwise.
    */ 
    public static function create($username, $password, $name, $email)
    { 
        try 
        {
            return DB::table('users')->insert(['username' => $username, 'name' => $name, 
                'password' => password_hash($password, PASSWORD_BCRYPT), 'email' => $email, 
                'isTeacher' => false]);
        } 
        catch (\Exception $e) 
        {
            return false;
        }
    }

    /** 
     * This function will check if a username already exists
     * @param $username The username to check
     * @return bool true if exists, false otherwise
    */ 
    public static function checkUserExists($username)
    { 
        try 
        {
            $user = DB::table('users')->select('*')->where('username', '=', $username)->get();
            if(count($user) != 0)
                return true;
        } 
        catch (\Exception $e) 
        {
            return true;
        }

        return false;
    }
}

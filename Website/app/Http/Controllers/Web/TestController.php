<?php

namespace App\Http\Controllers\Web;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use DB;

class TestController extends Controller
{
    /**
     * Adds a tip to a given unit test.
     *
     * @param $request the received request
     * @param $id the id of the test
     *
     * @return 403 if permissions error, 500 if DB error or 200 if success
     */
    public function addTipToExercise(Request $request, $id)
    {
        try
        {
            if (!($request->ajax() || $request->pjax() || Auth::check()))
            {
                return response('Forbidden.', 403);
            }

            $tip = $request->input('tip');

            DB::update('UPDATE Test SET hint = ? WHERE id = ?', [$tip, $id]);
        }
        catch (Exception $e)
        {
            $this->error($e);

            return response('Internal Error', 500);
        }

        return response('Success', 200);
    }
}

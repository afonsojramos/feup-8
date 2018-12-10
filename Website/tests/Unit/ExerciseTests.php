<?php

namespace Tests\Unit;

use Tests\TestCase;
use App\Http\Controllers\API\ExerciseController;

class ExerciseTests extends TestCase
{
    //Test checkExerciseStudentExists

    /**
     * Tests if the checkExerciseStudentExists method returns true for a student with one or more entries to exerciseSudent table.
     */
    public function testCheckExerciseStudentExistsTrueCase()
    {
        $exercise_id = 1;
        $logged_user_id = 1;
        $this->assertTrue(ExerciseController::checkExerciseStudentExists($exercise_id, $logged_user_id));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false when entrie not exists in exerciseSudent table.
     */
    public function testCheckExerciseStudentExistsWhenEntryNotExistsInExerciseStudent()
    {
        $exercise_id = 2;
        $logged_user_id = 1;
        $this->assertFalse(ExerciseController::checkExerciseStudentExists($exercise_id, $logged_user_id));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false for a student that doesn't exist.
     */
    public function testCheckExerciseStudentExistsWhenStudentDoesNotExist()
    {
        $exercise_id = 1;
        $logged_user_id = 0;

        $this->assertFalse(ExerciseController::checkExerciseStudentExists($exercise_id, $logged_user_id));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false for an exercise that doesn't exist.
     */
    public function testCheckExerciseStudentExistsWhenExerciseDoesNotExist()
    {
        $exercise_id = 0;
        $logged_user_id = 1;
        $this->assertFalse(ExerciseController::checkExerciseStudentExists($exercise_id, $logged_user_id));
    }

    //Test getExerciseResolutionProgressBasedOnStudentCode

    /**
     * Generic method used for testing getExerciseResolutionProgressBasedOnStudentCode method.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestGetExerciseResolutionProgressBasedOnStudentCode($exercise_id, $test_code, $expected_progress)
    {
        $exerciseController = new ExerciseController();
        $this->assertEquals($exerciseController->getExerciseResolutionProgressBasedOnStudentCode($exercise_id, $test_code), $expected_progress);
    }

    /**
     * Tests if the getExerciseResolutionProgressBasedOnStudentCode method for a non existing exercise, so with no tests. The expected return indicating error is -1;.
     */
    public function testGetExerciseResolutionProgressBasedOnStudentCode()
    {
        $exercise_id = 5;
        $test_code = 'test_code';
        $expected_progress = -1;
        $this->genericTestGetExerciseResolutionProgressBasedOnStudentCode($exercise_id, $test_code, $expected_progress);
    }

    /**
     * Tests if the getExerciseResolutionProgressBasedOnStudentCode method when an exercises with 2 tests, only passes one, corresponding to an expected progress of 50.
     */
    public function testGetExerciseResolutionProgressBasedOnStudentCodePartialCorrect()
    {
        $exercise_id = 1;
        $test_code = 'ZnVuY3Rpb24gc3VtKG51bTEsIG51bTIpDQogICAgICAgIHJldHVybiBudW0xICsgbnVtMjsNCiAgICAgZW5k';  //function sum(num1, num2) \n return num1 + num2; \n end
        $expected_progress = 50;
        $this->genericTestGetExerciseResolutionProgressBasedOnStudentCode($exercise_id, $test_code, $expected_progress);
    }

    /**
     * Tests if the getExerciseResolutionProgressBasedOnStudentCode method when an exercises with 2 tests, none passes, corresponding to an expected progress of 0.
     */
    public function testGetExerciseResolutionProgressBasedOnStudentCodeWrong()
    {
        $exercise_id = 2;
        $test_code = 'ZnVuY3Rpb24gc3VtKG51bTEsIG51bTIpDQogICAgICAgIHJldHVybiBudW0xICsgbnVtMjsNCiAgICAgZW5k';  //function sum(num1, num2) \n return num1 + num2; \n end
        $expected_progress = 0;
        $this->genericTestGetExerciseResolutionProgressBasedOnStudentCode($exercise_id, $test_code, $expected_progress);
    }

    //Test getExerciseTestsTestCode

    /**
     * Tests if the getExerciseTestsTestCode method return the expected test_code for the tests existent in the tests database for public exercise.
     */
    public function testGetExerciseTestsTestCodeForPublicExercise()
    {
        $exerciseController = new ExerciseController();
        $excepted_array_exercise_tests_received = array(
            array('test_code' => "function test_sum_failing()\nluaunit.assertEquals(sum(3, 4), 8)\nluaunit.assertEquals(sum(4, 3), 9)\nluaunit.assertEquals(sum(3, -4), -7)\nend"),
            array('test_code' => "function test_sum_failing2()\nluaunit.assertEquals(sum(3, 4), 8)\nluaunit.assertEquals(sum(4, 3), 9)\nluaunit.assertEquals(sum(3, -4), -7)\nend"), );

        $this->assertEquals(
            $exerciseController->getExerciseTestsTestCode(2, 0),
            json_decode(json_encode($excepted_array_exercise_tests_received))
        );
    }

    /**
     * Tests if the getExerciseTestsTestCode method returns nothing when exercise is private and student has no permissions.
     */
    public function testGetExerciseTestsTestCodeForPrivateExerciseWithoutPermissions()
    {
        $exerciseController = new ExerciseController();
        $this->assertEmpty($exerciseController->getExerciseTestsTestCode(3, 0));
    }

    /**
     * Tests if the testGetExerciseTestsTestCodeForPublicExercise method return the expected test_code for the tests existent in the tests database for public exercise.
     */
    public function testGetExerciseTestsTestCodeForPrivateExerciseWithPermission()
    {
        $exerciseController = new ExerciseController();
        $excepted_array_exercise_tests_received = array(
            array('test_code' => "function test_sum_correct()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend"),
            array('test_code' => "function test_sum_failing()\nluaunit.assertEquals(sum(3, 4), 8)\nluaunit.assertEquals(sum(4, 3), 9)\nluaunit.assertEquals(sum(3, -4), -7)\nend"), );
        $this->assertEquals(
            $exerciseController->getExerciseTestsTestCode(1, 1),
            json_decode(json_encode($excepted_array_exercise_tests_received))
        );
    }

    //Test testExerciseCodeUsingLuaUnitExecutor

    /**
     * Generic method used for testing testExerciseCodeUsingLuaUnitExecutor method.
     * It should be called with data that either causes success or not and the expected returns accordingly.
     * It is used to test success and failure avoiding code duplication.
     */
    public function genericTestExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array, $expected_return_code)
    {
        $exerciseController = new ExerciseController();
        $this->assertEquals($exerciseController->testExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array)[0], $expected_return_code);
    }

    /**
     * Tests if the testExerciseCodeUsingLuaUnitExecutor method return the expected return code 0 for a code that make pass all tests.
     */
    public function testTestExerciseCodeUsingLuaUnitExecutorAllTestPass()
    {
        $code = "function sum(num1, num2) \n return num1 + num2; \n end";
        $unit_tests_code_array = [
            "function test_sum_correct()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend",
            "function test_sum_correct2()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend", ];
        $expected_return_code = 0;
        $this->genericTestExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array, $expected_return_code);
    }

    /**
     * Tests if the testExerciseCodeUsingLuaUnitExecutor method return the expected return code 2(number of tests done) for a code that make all tests fail.
     */
    public function testTestExerciseCodeUsingLuaUnitExecutorAllTestFail()
    {
        $code = "function sum(num1, num2) \n return num1 - num2; \n end";
        $unit_tests_code_array = [
            "function test_sum_correct()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend",
            "function test_sum_correct2()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend", ];
        $expected_return_code = 2;
        $this->genericTestExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array, $expected_return_code);
    }

    /**
     * Tests if the testExerciseCodeUsingLuaUnitExecutor method return the expected return code 0 for a code that make all tests fail.
     */
    public function testTestExerciseCodeUsingLuaUnitExecutorTestsWithSyntaticErrors()
    {
        $code = 'djlkdjglkdsjgldsljgjsdlk'; //code with syntatic errors
        $unit_tests_code_array = [
            "function test_sum_correct()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend",
            "function test_sum_correct2()\nluaunit.assertEquals(sum(3, 4), 7)\nluaunit.assertEquals(sum(4, 3), 7)\nluaunit.assertEquals(sum(3, -4), -1)\nend", ];
        $expected_return_code = -1;
        $this->genericTestExerciseCodeUsingLuaUnitExecutor($code, $unit_tests_code_array, $expected_return_code);
    }
}

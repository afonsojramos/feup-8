<?php

namespace Tests\Unit;

use Tests\TestCase;
use Illuminate\Foundation\Testing\RefreshDatabase;
use App\Http\Controllers\API\ExerciseController; 

class ExerciseTests extends TestCase
{
    //Test checkExerciseStudentExists

    /**
     * Tests if the checkExerciseStudentExists method returns true for a student with one or more entries to exerciseSudent table.
    */
    public function testCheckExerciseStudentExistsTrueCase()
    {
        $this->assertTrue(ExerciseController::checkExerciseStudentExists(1, 1));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false when entrie not exists in exerciseSudent table.
    */
    public function testCheckExerciseStudentExistsWhenEntryNotExistsInExerciseStudent()
    {
        $this->assertFalse(ExerciseController::checkExerciseStudentExists(2, 1));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false for a student that doesn't exist.
    */
    public function testCheckExerciseStudentExistsWhenStudentDoesNotExist()
    {
        $this->assertFalse(ExerciseController::checkExerciseStudentExists(1, 0));
    }

    /**
     * Tests if the checkExerciseStudentExists method returns false for an exercise that doesn't exist.
    */
    public function testCheckExerciseStudentExistsWhenExerciseDoesNotExist()
    {
        $this->assertFalse(ExerciseController::checkExerciseStudentExists(0, 1));
    }
}

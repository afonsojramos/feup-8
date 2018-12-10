<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateExerciseStudentTable extends Migration
{
    /**
     * Run the migrations.
     */
    public function up()
    {
        Schema::create('ExerciseStudent', function (Blueprint $table)
        {
            $table->integer('student_id');
            $table->foreign('student_id')->references('id')->on('users')->onDelete('cascade');
            $table->integer('exercise_id');
            $table->foreign('exercise_id')->references('id')->on('Exercise')->onDelete('cascade');
            $table->integer('progress')->nullable();
            $table->binary('feup8_file');
            $table->primary(['student_id', 'exercise_id']);
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down()
    {
        Schema::dropIfExists('ExerciseStudent');
    }
}

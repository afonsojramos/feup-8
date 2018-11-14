<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateExerciseTable extends Migration
{
    /**
     * Run the migrations.
     */
    public function up()
    {
        Schema::create('Exercise', function (Blueprint $table)
        {
            $table->increments('id')->unique();
            $table->string('title')->unique();
            $table->string('description');
            $table->string('image_path')->unique();
            $table->integer('creator_id');
            $table->foreign('creator_id')->references('id')->on('users')->onDelete('cascade');
            $table->boolean('isPrivate');
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down()
    {
        Schema::dropIfExists('Exercise');
    }
}

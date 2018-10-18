<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateTestTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('Test', function (Blueprint $table) {
            $table->increments('id')->unique();
            $table->string('title');
            $table->integer('exercise_id');
            $table->foreign('exercise_id')->references('id')->on('Exercise')->onDelete('cascade');
            $table->string('test_code');
            $table->string('hint')->nullable();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('Test');
    }
}

<?php

use Illuminate\Database\Seeder;

class TestsSeeder extends Seeder
{
    /**
     * Seeds the test database.
     */
    public function run()
    {
        Eloquent::unguard();
        $path = 'database/database_tests_data.sql';
        DB::unprepared(file_get_contents($path));
    }
}

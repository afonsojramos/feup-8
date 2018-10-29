<?php

use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     * @return void
     */
    public function run()
    {
        Eloquent::unguard();
        $path = 'database/data.sql';
        DB::unprepared(file_get_contents($path));
    }
}

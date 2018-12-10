#!/bin/bash
#Sets correct database path

composer install
php artisan migrate:refresh
php artisan db:seed --class=TestsSeeder


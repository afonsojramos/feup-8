#!/bin/bash
#Sets correct database path

composer install
php artisan migrate:refresh --env=testing
php artisan db:seed --class=TestsSeeder --env=testing


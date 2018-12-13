#!/bin/bash

php artisan migrate:refresh
php artisan db:seed --class=TestsSeeder
php artisan passport:install

./vendor/bin/phpunit --testdox --coverage-html report

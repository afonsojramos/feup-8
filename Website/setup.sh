#!/bin/bash
#Sets correct database path
sed -i 's?DB_DATABASE=.*$?DB_DATABASE='`pwd`'/database/database_tests.sqlite?' .env

touch database/database_tests.sqlite
composer install
php artisan migrate --seed
php artisan passport:install --force

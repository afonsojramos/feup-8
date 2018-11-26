#!/bin/bash
#Sets correct database path
sed -i 's?DB_DATABASE=.*$?DB_DATABASE='`pwd`'/database/database_tests.sqlite?' .env.testing

touch database_tests.sqlite
composer install
php artisan migrate --env=testing
php artisan passport:install --env=testing

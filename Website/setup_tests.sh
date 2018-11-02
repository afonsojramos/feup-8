cd database
touch database_tests.sqlite
cd ..
composer install
php artisan migrate --env=testing
php artisan passport:install --env=testing

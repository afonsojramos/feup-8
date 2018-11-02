cd database
touch database_tests.sqlite
cd ..
composer install
php artisan migrate
composer require laravel/passport
php artisan passport:install

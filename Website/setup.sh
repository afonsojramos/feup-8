cd database
touch database.sqlite
cd ..
composer install
composer require laravel/passport
php artisan migrate
php artisan passport:install

cd database
touch database.sqlite
cd ..
composer install
php artisan migrate
composer require laravel/passport
php artisan passport:install

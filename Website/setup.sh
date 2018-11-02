cd database
touch database.sqlite
cd ..
composer install
php artisan migrate --seed
php artisan passport:install

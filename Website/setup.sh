touch database/database_testing.sqlite
composer install
php artisan migrate --seed
php artisan passport:install --force

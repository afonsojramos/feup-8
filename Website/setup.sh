touch database/database.sqlite
composer install
php artisan migrate --seed
php artisan passport:install --force

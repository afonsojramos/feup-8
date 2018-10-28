cd database
rm database_test.sqlite
touch database_test.sqlite
cd ..
APP_ENV=testing php artisan migrate
./vendor/bin/phpunit

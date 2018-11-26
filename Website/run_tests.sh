APP_ENV=testing php artisan migrate:refresh
APP_ENV=testing php artisan passport:install
cd database
sqlite3 database_tests.sqlite < database_tests_data.sql
cd ..
APP_ENV=testing ./vendor/bin/phpunit --testdox --coverage-html report

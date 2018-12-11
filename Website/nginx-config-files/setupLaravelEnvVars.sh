#!bin/bash

#This adds to Laravel's .env some environment variables passed from CI to docker-compose
#and finally this container

cp /var/www/laravel/nginx-config-files/.env.prod /var/www/laravel/nginx-config-files/.env 

echo 'APP_KEY='$APP_KEY >> /var/www/laravel/.env
echo 'DB_PASSWORD='$DB_PASSWORD >> /var/www/laravel/.env

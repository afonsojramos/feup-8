#!/bin/bash

# Stop execution if a step fails
set -e

server_name=$1

if [ $server_name != 'staging' ] && [ $server_name != 'prod' ]
then
    echo 'FAILURE No server named '$server_name
    exit 2
fi


#Copies the server files to the right location
cp /web/nginx-config-files/sites-available/default /etc/nginx/sites-available/
ln -s -f /etc/nginx/sites-available/default /etc/nginx/sites-enabled
mkdir -p /var/www/laravel/
cp -r /web/. /var/www/laravel/

chmod -R 0777 /var/www

#Sets Laravel .env file
/web/nginx-config-files/setupLaravelEnvVars.sh

#Seeds PostgresDB
bash -c "cd /var/www/laravel/ && /var/www/laravel/setup.sh"


#Create user for server requests
usermod -a -G www-data www-data

#Create and give rw permissions to php7.2-fpm.sock to all
mkdir -p /var/run/php/
touch /var/run/php/php7.2-fpm.sock
chmod 0666 /var/run/php/php7.2-fpm.sock
chown www-data /var/run/php/php7.2-fpm.sock

service php7.2-fpm restart

#!/bin/bash

composer install
php artisan migrate:refresh --seed
php artisan passport:install --force

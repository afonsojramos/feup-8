#!/bin/bash

composer install
php artisan migrate:refresh --seed --force
php artisan passport:install --force

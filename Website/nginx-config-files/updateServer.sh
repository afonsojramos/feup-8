#!/bin/bash

# Stop execution if a step fails
set -e

if [ $# -eq 0 ]
then
    echo $(date --iso-8601=seconds)' FAILURE No server name was provided' >>  /var/log/server-updates-history
    echo No agument provided
    exit 1
fi

server_name=$1

if [ server_name != 'staging' ] && [ server_name != 'prod' ]
then
    echo $(date --iso-8601=seconds)' FAILURE No server named '$server_name >>  /var/log/server-updates-history
    exit 2
fi




#Laravel Vars
echo 'APP_KEY='$2 > /.env
echo 'DB_HOST=postgres-'server_name > /.env 
echo 'DB_PASSWORD='$3 >> /.env


#Docker commands
docker-compose -f /docker-compose.prod.yml stop web-$server_name postgres-$server_name

docker pull registry.gitlab.com/feup-tbs/ldso18-19/t5g2:website-$server_name
docker-compose -f /docker-compose.prod.yml up -d web-$server_name postgres-$server_name

echo $(date --iso-8601=seconds)' Successfully updated '$server_name >>  /var/log/server-updates-history

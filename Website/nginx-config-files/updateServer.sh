#!/bin/bash

if [ $# -eq 0 ]
then
    echo $(date --iso-8601=seconds)' FAILURE No server name was provided' >>  /var/log/server-updates-history
    echo No agument provided
    exit 1
fi

cd /root/t5g2

server_name=$1

if [ $1 == 'prod' ] 
then
    git checkout master

elif [ $1 == 'staging' ]
then
    git checkout development

else
    echo $(date --iso-8601=seconds)' FAILURE No server named '$server_name >>  /var/log/server-updates-history
    exit 2
fi

git pull


#Docker commands
docker-compose -f docker-compose.prod.yml stop web-$server_name
docker-compose -f docker-compose.prod.yml  up --build -d web-$server_name

echo $(date --iso-8601=seconds)' Successfully updated '$server_name >>  /var/log/server-updates-history


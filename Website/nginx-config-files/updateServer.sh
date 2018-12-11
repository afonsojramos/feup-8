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

<<<<<<< HEAD

if [ $server_name != 'staging' ] && [ $server_name != 'prod' ]
=======
if [ server_name != 'staging' ] && [ server_name != 'prod' ]
>>>>>>> development
then
    echo $(date --iso-8601=seconds)' FAILURE No server named '$server_name >>  /var/log/server-updates-history
   exit 2
fi

<<<<<<< HEAD
=======



#Laravel Vars
echo 'APP_KEY='$2 > /.env
echo 'DB_HOST=postgres-'server_name > /.env 
echo 'DB_PASSWORD='$3 >> /.env
>>>>>>> development



#Laravel Vars
echo 'APP_KEY='$2 > /.env
echo 'DB_HOST=postgres-'$server_name >> /.env
echo 'DB_PASSWORD='$3 >> /.env

#Go to / due to /.env to be accessible by docker-compose
cd /

#Docker commands
docker-compose -f /docker-compose.prod.yml stop web-$server_name postgres-$server_name
<<<<<<< HEAD

docker pull registry.gitlab.com/feup-tbs/ldso18-19/t5g2:website-$server_name
docker-compose -f /docker-compose.prod.yml up -d web-$server_name postgres-$server_name
=======
>>>>>>> development

docker pull registry.gitlab.com/feup-tbs/ldso18-19/t5g2:website-$server_name
docker-compose -f /docker-compose.prod.yml up -d web-$server_name postgres-$server_name

<<<<<<< HEAD
#Delete dockerfile's  temp env file 
rm /.env
=======
echo $(date --iso-8601=seconds)' Successfully updated '$server_name >>  /var/log/server-updates-history
>>>>>>> development

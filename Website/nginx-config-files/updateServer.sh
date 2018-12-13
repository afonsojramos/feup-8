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


if [ $server_name != 'staging' ] && [ $server_name != 'prod' ]
then
    echo $(date --iso-8601=seconds)' FAILURE No server named '$server_name >>  /var/log/server-updates-history
    exit 2
fi




#Laravel Vars
touch /.env
echo 'APP_KEY='$2 > /.env
echo 'DB_HOST=postgres-'$server_name >> /.env
echo 'DB_PASSWORD='$3 >> /.env



#Laravel Vars
echo 'APP_KEY='$2 > /.env
echo 'DB_HOST=postgres-'$server_name >> /.env
echo 'DB_PASSWORD='$3 >> /.env

#Go to / due for /.env to be accessible by docker-compose
cd /

#Docker commands
docker-compose -f /docker-compose.prod.yml stop web-$server_name postgres-$server_name

docker pull registry.gitlab.com/feup-tbs/ldso18-19/t5g2:website-$server_name
docker-compose -f /docker-compose.prod.yml up --build -d  web-$server_name postgres-$server_name

#Wait to assert if the server is really alive
sleep 10

srv_bool=$(docker inspect -f {{.State.Running}} web-$server_name)
db_bool=$(docker inspect -f {{.State.Running}} postgres-$server_name)


if [ $srv_bool = 'false' ] || [ $db_bool = 'false' ]
then
	echo 'FAILURE - '$server_name' down...'
	echo $(date --iso-8601=seconds)' Failed starting '$server_name' docker container' >>  /var/log/server-updates-history
	exit 3
fi

echo 'SUCCESS - '$server_name' running!!!!!'
echo $(date --iso-8601=seconds)' Successfully updated '$server_name >>  /var/log/server-updates-history

#Delete dockerfile's  temp env file
rm /.env

# Ubuntu image
FROM ubuntu:18.04

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /web
RUN apt-get update -y && apt-get install -y apt-utils openssl zip unzip git tzdata

RUN  echo "Europe/Dublin" > /etc/timezone && dpkg-reconfigure -f noninteractive tzdata

# Install nginx
RUN apt-get install -y nginx

#Install PHP
RUN apt-get install -y curl php7.2-cli php7.2-fpm php7.2-curl php7.2-gd php7.2-pgsql php7.2-mbstring zip unzip php7.2-xml php7.2-xdebug 


#Install Nodejs
RUN apt-get install -y nodejs npm 


RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer


# Lua dependencies
RUN apt-get install -y lua50        # Lua intepreter
RUN apt-get install -y luarocks     # Lua package manager
RUN apt-get install -y luajit       # Lua JIT compiler to validate syntax
RUN luarocks install luaunit        # LuaUnit library



COPY . /web

RUN composer install

# Run the server
CMD php artisan serve --env=testing --host=0.0.0.0 --port=8000

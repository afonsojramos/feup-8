# PHP dependencies
FROM php:7
RUN apt-get update -y && apt-get install -y openssl zip unzip git
RUN curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer
RUN docker-php-ext-install pdo mbstring
WORKDIR /app
COPY . /app
RUN composer install

# Lua dependencies
RUN apt-get install -y lua50        # Lua intepreter
RUN apt-get install -y luarocks     # Lua package manager
RUN apt-get install -y luajit       # Lua JIT compiler to validate syntax
RUN luarocks install luaunit        # LuaUnit library

# Run the server
CMD php artisan serve --host=0.0.0.0 --port=8000
EXPOSE 8181

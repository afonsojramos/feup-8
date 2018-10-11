#!/bin/bash

cd src
gcc -I../include -I../3rd-party/blip-buf -I../3rd-party/wren-0.1.0/src/include -I../3rd-party/sdl-gpu/include -I../3rd-party/lua-5.3.1/src -I../3rd-party/duktape-2.2.0/src -I../3rd-party/moonscript -I../3rd-party/SDL2-2.0.8/include -I../3rd-party/SDL2_net-2.0.1 -I../3rd-party/fennel *.c -o tests -Wall
./tests

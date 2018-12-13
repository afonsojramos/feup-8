#!/bin/bash

cmake . && make -j4 || exit 1
yes | cp -rf ./assets/conf.ini ./bin/conf.ini
cd bin
./tic80

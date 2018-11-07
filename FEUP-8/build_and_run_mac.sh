#!/bin/bash

cmake . && make -j4 || exit 1  
./bin/tic80pro.app/Contents/MacOS/tic80pro

#!/bin/bash

cmake . && make -j4 || exit 1
cd bin 
./tic80

#!/bin/bash

cmake . && make -j4
cd bin
./tic80 -test

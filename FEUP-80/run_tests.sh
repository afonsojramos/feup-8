#!/bin/bash

cd src/test
gcc *.c -o tests -Wall
./tests

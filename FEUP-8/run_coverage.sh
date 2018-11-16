#!/bin/bash

cmake . && make -j4
make tic80_coverage

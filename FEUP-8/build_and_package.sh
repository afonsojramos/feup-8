#!/bin/bash

cmake . && make -j4 || exit 1
sh package.sh

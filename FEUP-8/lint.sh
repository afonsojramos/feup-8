#!/bin/bash

# DO NOT RUN AS sh lint.sh
# RUN AS ./lint.sh instead

if ! [ -x "$(command -v clang-format)" ]; then
  echo 'Error: clang-format is not installed. Please install it to run the linter.' >&2
  exit 1
fi

# Run the linter
echo "Running linter for C files..."
clang-format -i ./src/*.c ./include/*.h ./src/*.h ./src/system/*.c ./src/ext/*.c ./src/ext/*.h ./src/ext/*.cpp

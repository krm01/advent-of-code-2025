#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
bin=main

g++ -std=c++23 $1 "$SCRIPT_DIR/utils.cpp" -o "$bin"
if [ $? -eq 0 ]; then
    time ./"$bin"
    rm "$bin"
fi

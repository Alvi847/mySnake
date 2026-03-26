#!/bin/bash

cd build

make
if [ $? = 0 ]; then
    ./mySnake
fi

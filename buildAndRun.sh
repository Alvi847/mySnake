#!/bin/bash

cd build

make
if [ $? = 0 ]; then
    echo "fasfdasdgfsedagsad"
    ./mySnake
fi

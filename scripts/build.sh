#!/bin/bash

target_release() {
    cd release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    make
    echo "Built target in build/release/"
    cd ../..
}

target_debug() {
    cd debug 
    cmake -DCMAKE_BUILD_TYPE=Debug ../..
    make
    echo "Built target in build/debug/"
    cd ../..
}

# Create folder for distribution
if [ "$1" = "release" ]
then
    if [ -d "$Tetris" ]
    then
        rm -rf -d Tetris
    fi

    mkdir -p Tetris
fi

# Creates the folder for the buildaries
mkdir -p Tetris 
mkdir -p Tetris/assets
mkdir -p build
mkdir -p build/release
mkdir -p build/debug
cd build

# Builds target
if [ "$1" = "release" ]
then
    target_release
    cp build/release/Tetris Tetris/Tetris
else
    target_debug
fi

cp -R assets Tetris/

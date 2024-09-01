#!/bin/bash

if [ "$1" = "release" ]
then
    ./build/release/Tetris
else
    ./build/debug/Tetris
fi
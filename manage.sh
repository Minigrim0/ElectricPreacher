#!/bin/bash

# Check if first argument is "build"
if [ "$1" == "build" ]; then
    if [ "$2" == "release" ]; then
        echo "Building release..."
        make config=release
    else
        echo "Building debug..."
        make config=debug
    fi
elif [ "$1" == "generate" ]; then
    ./vendor/unix/premake/premake5 gmake2
elif [ "$1" == "clean" ]; then
    make clean
elif [ "$1" == "graph" ]; then
    python3 graph/graph.py
elif [ "$1" == "run" ]; then
    if [ "$2" == "release" ]; then
        echo "Running release..."
        ./bin/Release-linux-x86_64/ElectricPreacher/ElectricPreacher
    else
        echo "Running debug..."
        ./bin/Debug-linux-x86_64/ElectricPreacher/ElectricPreacher
    fi
elif [ $1 == "debug" ]; then
    if [ "$2" == "release" ]; then
        echo "Debugging release..."
        gdb ./bin/Release-linux-x86_64/ElectricPreacher/ElectricPreacher
    else
        echo "Debugging debug..."
        gdb ./bin/Debug-linux-x86_64/ElectricPreacher/ElectricPreacher
    fi
else
    echo "Usage: ./manage.sh [build|generate|clean|graph|run|debug] [release|debug]"
fi

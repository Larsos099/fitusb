#!/bin/bash

make="make"
ninja="ninja"
tool=0

echo "Checking for Ninja..."
if command -v "$ninja" >/dev/null 2>&1; then
    echo "Found Ninja"
    tool=1
    cmake --preset unix-ninja
    exit 0
fi

echo "Checking for Make..."
if command -v "$make" >/dev/null 2>&1; then
    echo "Found Make"
    tool=1
    cmake --preset unix
    exit 0
fi

if [ "$tool" -eq 0 ]; then
    echo "Could not find either Ninja, nor $make"
    echo "Please install one of them. (Preferred: Ninja)"
    exit 1
fi
#!/bin/sh

set -e

mkdir build/ || true
cd build/
cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build .

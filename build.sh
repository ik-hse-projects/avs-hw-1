#!/bin/sh

set -e

mkdir build/ || true
cd build/
cmake "$@" ../
cmake --build .

#!/bin/sh

cd build/src
./icfpc2020 "$@" || echo "run error code: $?"


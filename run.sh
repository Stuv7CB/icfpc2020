#!/bin/sh

cd build
./icfpc2020 "$@" || echo "run error code: $?"


#!/usr/bin/env bash

set -e
pushd build

# compile
make

# run unit tests
./tests/testOpenLib
./examples/OpenLibExamples

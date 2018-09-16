#!/usr/bin/env bash
mkdir -p builds/ci-build
cd builds/tidy-build
CC=clang CXX=clang++ cmake ../..
make

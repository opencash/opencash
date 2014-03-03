#!/bin/bash

echo "PATH: $PATH"

echo "g++ at `which g++`"
echo "GCC g++ version: `g++ --version`"
echo "GCC g++ dumpmachine: `g++ -dumpmachine`"

echo "clang++ at `which clang++`"
echo "Clang clang++ version: `clang++ --version`"
echo "Clang clang++ dumpmachine: `clang++ -dumpmachine`"

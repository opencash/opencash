#!/bin/bash

echo "PATH: $PATH"

echo "GCC gcc version: `gcc --version`"
echo "GCC gcc dumpmachine: `gcc -dumpmachine`"
echo "GCC g++ version: `g++ --version`"
echo "GCC g++ dumpmachine: `g++ -dumpmachine`"

echo "Clang clang version: `clang --version`"
echo "Clang clang dumpmachine: `clang -dumpmachine`"
echo "Clang clang++ version: `clang++ --version`"
echo "Clang clang++ dumpmachine: `clang++ -dumpmachine`"

sudo apt-get update
echo "apt-get search gcc: `apt-cache search gcc`"
echo "apt-get search clang: `apt-cache search gcc`"

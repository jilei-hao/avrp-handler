#! /bin/bash

# This script is an example of how to configure a C++ project using CMake.
# execute this script from the root of the project.
cmake -S ./cpp -B ./build \
  -DCMAKE_BUILD_TYPE=Debug
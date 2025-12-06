#!/bin/bash

conan install . --output-folder=build_conan --build=missing -s build_type=Debug -pr=default -pr=conan_profile.txt

cmake --preset debug
cmake --build --preset debug

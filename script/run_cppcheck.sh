#!/bin/bash

cppcheck \
    --enable=all \
    --std=c++20 \
	--template="{file}:{line}:{column}: {severity}: {message}" \
	--quiet \
	--suppress=checkersReport \
	--suppress=missingIncludeSystem \
    -i vcpkg \
    -i build_debug \
    -i build_develop \
    -i build_release \
    .

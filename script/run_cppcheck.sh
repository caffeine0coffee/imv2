#!/bin/bash

devbox run cppcheck "$@" \
    --enable=all \
    --std=c++20 \
	--quiet \
	--suppress=checkersReport \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude \
    -i vcpkg \
    -i build_debug \
    -i build_develop \
    -i build_release \
    .

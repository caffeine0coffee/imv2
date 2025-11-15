#!/bin/bash

# This script runs cppcheck using devbox.
# All arguments passed to this script are forwarded directly to cppcheck.
# Use this script when checking a single file or when integrating with an editor.
# To check the entire project, run run_cppcheck_all.sh instead.

devbox run cppcheck \
    --enable=all \
    --std=c++20 \
	--quiet \
	--suppress=checkersReport \
	--suppress=missingIncludeSystem \
	--suppress=missingInclude \
	"$@"

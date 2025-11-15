#!/bin/bash

# This script checks the entire project using run_cppcheck.sh.
# Note that all arguments passed to this script are ignored.
# If you want to check a single file or integrate with an editor,
# use run_cppcheck.sh directly.
#
# [!] This script returns 0 regardless of cppcheck results to avoid CI failures.

script_dir=$(readlink -f "$(dirname "$0")")
project_dir=$(readlink -f "${script_dir}/..")

"${script_dir}/run_cppcheck.sh" \
    -i vcpkg \
    -i build_debug \
    -i build_debug_windows \
    -i build_develop \
    -i build_release \
	"${project_dir}"

exit 0

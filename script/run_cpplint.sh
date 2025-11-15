#!/bin/bash

# This script runs cpplint using devbox.
# All arguments passed to this script are forwarded directly to cpplint.
# Use this script when checking a single file or when integrating with an editor.
# To check the entire project, run run_cpplint_all.sh instead.

devbox run cpplint --linelength=120 "$@"

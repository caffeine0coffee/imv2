#!/bin/bash

set -euo pipefail

rm -rf build_conan

conan_args=(
  --output-folder=build_conan
  --build=missing
  -s
  build_type=Debug
  -pr=default
  -pr=conan_profile.txt
)

if [[ "$(uname -s)" == "Darwin" ]]; then
  # macOS 13.3 をデフォルトデプロイターゲットに固定
  export MACOSX_DEPLOYMENT_TARGET="${MACOSX_DEPLOYMENT_TARGET:-13.3}"
  conan_args+=(-s:h "os.version=${MACOSX_DEPLOYMENT_TARGET}")
fi

conan install . "${conan_args[@]}"

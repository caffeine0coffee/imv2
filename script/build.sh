#!/bin/bash

set -euo pipefail

# macOS 13.3 をデフォルトデプロイターゲットに固定
export MACOSX_DEPLOYMENT_TARGET="${MACOSX_DEPLOYMENT_TARGET:-13.3}"

# クリーンビルド（ユーザ要望に合わせ build_debug を毎回消す）
rm -rf build_debug

conan install . \
  --output-folder=build_conan \
  --build=missing \
  -s:h os.version="${MACOSX_DEPLOYMENT_TARGET}" \
  -s build_type=Debug \
  -pr=default \
  -pr=conan_profile.txt

cmake --preset debug
cmake --build --preset debug

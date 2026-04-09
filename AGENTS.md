# Repository Guidelines

AIによる回答はすべて日本語で行ってください。

## プロジェクト構成とモジュール整理
`src/`にはC++23ランタイム（render context、renderer、swapchain、resource managerなど）が入っています。新規モジュールは凝集度を保ち、プラットフォーム依存コードは分離してください。`script/`には`run_cppcheck.sh`などの自動化スクリプトが置かれています。CMake Presetは`build_debug`、`build_develop`、`build_release`に成果物を出力するため、生成物は各ディレクトリに閉じ込めましょう。`vcpkg/`と`vcpkg.json`がfmt、spdlog、vk-bootstrap、Vulkan、GLFWといった外部依存を固定します。Devboxマニフェストは再現性のあるツールチェーンを提供するので、新しい依存を追加するときはマニフェストも更新し、全員が同じ環境を再現できるようにします。

## Build, Test, and Development Commands
- `devbox shell` – Clang 21、CMake 4.1、cppcheck、X11依存を備えた再現ツールチェーンに入ります。
- `cmake --preset debug` – vcpkgツールチェーン込みで`build_debug`にNinja用設定を生成します。
- `cmake --build build_debug` – ビルドを実行します。最適化バイナリが欲しい場合は`--preset release`または`build_release`を使います。
- `./build_debug/imv2` – 変更ごとにローカルでモーションビジュアライザを動かし、状態遷移とリソースロードを確認します。
- `script/run_cppcheck.sh` – ベンダー／ビルドディレクトリを除外した静的解析を実行します。

## コーディングスタイルと命名規則
`.clang-format`はGoogleスタイル（2スペースインデント）を強制するため、コミット前に`clang-format -i path/to/file.cpp`を走らせてください。`.clang-tidy`（bugprone、cppcoreguidelines、modernize、performance、readability）で`clang-tidy -p build_debug src/foo.cpp`のように新規コードを検証し、CPPLintが軽量な追いチェックを行います。型名はパスカルケース（`Context`）、公開APIはlowerCamelCase、privateヘルパは末尾アンダースコア付きsnake_case（`create_swapchain_`）を使います。`#pragma once`や明示的な`namespace`、C++23機能（conceptsや`std::expected`）を優先し、独自マクロは避けてください。

## テスト指針
現状は自動テストがないため、すべての変更で`./build_debug/imv2`と`script/run_cppcheck.sh`（必要なら`clang-tidy`）を必ず実行し、退行を防ぎます。テストを追加する際は`tests/`を作成し、`add_test`で登録したうえで`ctest --test-dir build_debug --output-on-failure`で実行してください。GPUタイミングなど非決定的な検証は避け、必要なアセットはテストターゲットと同じ場所にコミットします。

## コミットとプルリクエスト
履歴はConventional Commits（`chore: add devbox depends for linux x11`）に従っているので、`<type>: <imperative summary>`形式を維持し、細かい修正はマージ前にスカッシュしてください。PRでは課題、解決策、検証ログ（コマンドや出力）を説明し、描画に触れた場合はスクリーンショットや動画も添付します。関連Issueをリンクし、担当レビュアに依頼し、Presetビルドがクリーンであることを確認してからマージします。

## 環境と依存関係
依存はvcpkgで解決するため、新しいライブラリは`vcpkg.json`に追加し、`devbox shell`内で`vcpkg install --triplet x64-linux`を実行してマニフェストとロックを同期させます。Vulkan/GLFWはホストGPUドライバに依存するためSDKパスをコミットせず、提供済みツールチェーンファイルを使ってください。ローカルのICD設定や秘密情報はバージョン管理に含めないようにします。

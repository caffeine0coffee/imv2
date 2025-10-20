#include <spdlog/spdlog.h>

#include "src/render_context.hpp"

int main() {
  spdlog::info("Hello, World!");

  const auto *const context = Context::Instance();
  const auto& vk_instance = context->vk_instance();
  spdlog::info("Context created!!!");

  return 0;
}

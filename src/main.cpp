#include <spdlog/spdlog.h>

#include "src/core/render_context.hpp"

int main() {
  spdlog::info("Hello, World!");

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  const auto* const context = Context::Instance();
  const auto& vk_instance = context->vk_instance();

  spdlog::info("Context created!!!");

  return 0;
}

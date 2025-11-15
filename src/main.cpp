#include <spdlog/spdlog.h>

#include "src/render_context.hpp"

#include <vulkan/vulkan.h>

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

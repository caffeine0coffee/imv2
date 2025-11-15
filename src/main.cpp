#include <spdlog/spdlog.h>

#include "src/render_context.hpp"

int main() {
  spdlog::info("Hello, World!");

  int* data = new int[10];

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  const auto* const context = Context::Instance();
  const auto& vk_instance = context->vk_instance();
  spdlog::info("Context createddfshjaklfhdjsklahfksdahlfhjdksahfkdhsajkhfjksdaklfhsdjkfshakhfjksdahkhjsdfkahklfhjaskl!!!");

  return 0;
}

#include <cstdlib>

#include <spdlog/spdlog.h>

#include "src/render_context.hpp"

int main() {
  spdlog::info("Hello, World!");

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  if (glfwInit() == GLFW_FALSE) {
    spdlog::error("Failed to initialize GLFW.");
    return EXIT_FAILURE;
  }
  std::atexit(glfwTerminate);

  const auto* const context = Context::Instance();
  const auto& vk_instance = context->vk_instance();

  spdlog::info("Context created!!!");

  return EXIT_SUCCESS;
}

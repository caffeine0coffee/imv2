#include <spdlog/spdlog.h>

#include "src/core/renderer.hpp"

int main() {
  spdlog::info("Starting application...");

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  // TODO(caffeine): create GLFW Window and initialize Context with its surface

  spdlog::trace("GLFW window created");

  const auto* const renderer = Renderer::Instance();

  spdlog::info("Context created!!!");

  return 0;
}

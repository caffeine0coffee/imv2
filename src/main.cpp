#include <cstdlib>
#include <memory>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <vulkan/vulkan.hpp>

#include "src/core/renderer.hpp"
#include "src/window.hpp"

int main() {
  spdlog::info("Starting application...");

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  Renderer::InitVulkanInstance();
  const auto window = std::make_unique<Window>();
  Renderer::InitVulkanDevice(window->vk_surface());

  Renderer::Instance()->draw();

  return EXIT_SUCCESS;
}

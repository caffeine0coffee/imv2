#include "src/window.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <stdexcept>

#include "src/core/renderer.hpp"

void Window::init_() {
  create_glfw_window_();
  create_vulkan_surface_();
}

void Window::destroy_() {
  auto vk_instance = Renderer::Instance()->vk_instance();
  vk_instance.destroySurfaceKHR(vk_surface_);
  spdlog::trace("Vulkan surface destroyed");

  glfwDestroyWindow(glfw_window_);
  spdlog::trace("GLFW window destroyed");

  glfwTerminate();
  spdlog::trace("GLFW terminated");
}

void Window::create_glfw_window_() {
  if (glfwInit() == GLFW_FALSE) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfw_window_ =
      glfwCreateWindow(kInitialWindowWidth, kInitialWindowHeight, "imv2", nullptr, nullptr);
  if (glfw_window_ == nullptr) {
    throw std::runtime_error("Failed to create GLFW window");
  }

  spdlog::trace("GLFW window created");
}

void Window::create_vulkan_surface_() {
  VkSurfaceKHR surface = nullptr;
  glfwCreateWindowSurface(Renderer::Instance()->vk_instance(), glfw_window_, nullptr, &surface);

  vk_surface_ = static_cast<vk::SurfaceKHR>(surface);
  spdlog::trace("Vulkan surface created");
}

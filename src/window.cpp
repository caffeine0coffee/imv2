#include "src/window.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <stdexcept>

Window::Window() { init_(); }

void Window::init_() {
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

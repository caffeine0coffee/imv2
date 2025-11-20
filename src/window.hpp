#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <vulkan/vulkan.hpp>

class Window {
 public:
  Window();

 private:
  void init_();

  static constexpr int kInitialWindowWidth = 800;
  static constexpr int kInitialWindowHeight = 600;

  GLFWwindow* glfw_window_{};
};

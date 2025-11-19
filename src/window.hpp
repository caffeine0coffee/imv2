#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

class Window {
 public:
 private:
  GLFWwindow* glfw_window_ = nullptr;
};

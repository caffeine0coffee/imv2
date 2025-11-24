#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include <vulkan/vulkan.hpp>

class Window {
 public:
  Window() { init_(); }
  Window(const Window&) = default;
  Window(Window&&) = delete;
  Window& operator=(const Window&) = default;
  Window& operator=(Window&&) = delete;
  ~Window() { destroy_(); }

  [[nodiscard]] vk::SurfaceKHR vk_surface() const { return vk_surface_; }

 private:
  void init_();
  void destroy_();
  void create_glfw_window_();
  void create_vulkan_surface_();

  static constexpr int kInitialWindowWidth = 800;
  static constexpr int kInitialWindowHeight = 600;

  GLFWwindow* glfw_window_{};
  vk::SurfaceKHR vk_surface_;
};

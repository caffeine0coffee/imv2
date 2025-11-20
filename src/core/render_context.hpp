#pragma once

#include <atomic>
#include <memory>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

#include <vulkan/vulkan.hpp>

class Context {
 public:
  static void Init(vk::SurfaceKHR vk_surface);
  static const Context* Instance();

  ~Context() { destroy_(); }
  Context(const Context&) = delete;
  Context(Context&&) = delete;
  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  [[nodiscard]] const vk::Instance& vk_instance() const { return vk_instance_; }

 private:
  static std::atomic<bool> initialized_;
  static std::mutex instance_mutex_;
  static std::unique_ptr<Context> instance_;

  explicit Context(vk::SurfaceKHR vk_surface) { init_(vk_surface); }

  void init_(vk::SurfaceKHR vk_surface);
  void destroy_();

  void create_vulkan_instance_();
  void create_glfw_window_();
  void create_vulkan_surface_();
  void create_swapchain_();
  void select_vulkan_physical_device_(vk::SurfaceKHR vk_surface);
  void create_vulkan_device_();

  const int kInitialWindowWidth = 800;
  const int kInitialWindowHeight = 600;

  vkb::Instance vkb_instance_;
  vk::Instance vk_instance_;

  vkb::PhysicalDevice vkb_physical_device_;
  vk::PhysicalDevice vk_physical_device_;

  vkb::Device vkb_device_;
  vk::Device vk_device_;

  GLFWwindow* glfw_window_ = nullptr;
};

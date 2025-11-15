#pragma once

#include <VkBootstrap.h>

#include <vulkan/vulkan.hpp>

class Context {
 public:
  static const Context* Instance();

  ~Context() { destroy_(); }
  Context(const Context&) = delete;
  Context(Context&&) = delete;
  Context& operator=(const Context&) = delete;
  Context& operator=(Context&&) = delete;

  [[nodiscard]] const vk::Instance& vk_instance() const { return vk_instance_; }

 private:
  Context() { init_(); }

  void init_();
  void destroy_();

  void create_vulkan_instance_();
  void create_swapchain_();
  void select_vulkan_physical_device_();
  void create_vulkan_device_();

  vkb::Instance vkb_instance_;
  vk::Instance vk_instance_;

  vkb::PhysicalDevice vkb_physical_device_;
  vk::PhysicalDevice vk_physical_device_;

  vkb::Device vkb_device_;
  vk::Device vk_device_;
};

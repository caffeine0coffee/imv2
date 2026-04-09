#pragma once

#include <atomic>
#include <memory>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <VkBootstrap.h>

#include <vulkan/vulkan.hpp>

class Renderer {
  class Context {
   public:
    Context() = default;
    ~Context() { destroy_(); }
    Context(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(const Context&) = delete;
    Context& operator=(Context&&) = delete;

    void init_vulkan_instance();
    void init_vulkan_device(VkSurfaceKHR vk_surface);

    [[nodiscard]] vk::Instance vk_instance() const;
    [[nodiscard]] vk::PhysicalDevice vk_physical_device() const;
    [[nodiscard]] vk::Device vk_device() const;

   private:
    void destroy_();

    std::atomic<bool> is_instance_initialized_{false};
    std::atomic<bool> is_device_initialized_{false};

    vkb::Instance vkb_instance_{};
    vk::Instance vk_instance_;

    vkb::PhysicalDevice vkb_physical_device_{};
    vk::PhysicalDevice vk_physical_device_;

    vkb::Device vkb_device_{};
    vk::Device vk_device_;
  };

 public:
  static void InitVulkanInstance();
  static void InitVulkanDevice(vk::SurfaceKHR vk_surface);
  static Renderer* Instance();

  ~Renderer() = default;
  Renderer() : context_(std::make_unique<Context>()) {}
  Renderer(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) = delete;

  void draw();

  [[nodiscard]] vk::Instance vk_instance() const { return context_->vk_instance(); }

 private:
  std::unique_ptr<Context> context_;
};

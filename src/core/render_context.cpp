#include "src/core/render_context.hpp"

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

const Context* Context::Instance() {
  static Context instance;
  return &instance;
}

void Context::init_() {
  create_vulkan_instance_();
  create_glfw_window_();
  create_vulkan_surface_();
  select_vulkan_physical_device_();
  create_vulkan_device_();
}

void Context::destroy_() {
  vkb::destroy_device(vkb_device_);
  vkb::destroy_surface(vkb_instance_, vk_surface_);
  vkb::destroy_instance(vkb_instance_);

  glfwDestroyWindow(glfw_window_);
  glfwTerminate();
}

void Context::create_vulkan_instance_() {
  vkb::InstanceBuilder builder;
  auto build_result = builder.set_app_name("imv2")
                          .request_validation_layers(true)
                          .require_api_version(1, 3, 0)
                          .build();
  if (!build_result) {
    const auto& error = build_result.error();
    throw std::runtime_error(fmt::format("Failed to create Vulkan instance: {}", error.message()));
  }

  vkb_instance_ = build_result.value();
  vk_instance_ = vkb_instance_.instance;

  spdlog::trace("Vulkan instance created");
}

void Context::create_glfw_window_() {
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

void Context::create_vulkan_surface_() {
  VkSurfaceKHR c_surface = VK_NULL_HANDLE;
  const auto& result = glfwCreateWindowSurface(vk_instance_, glfw_window_, nullptr, &c_surface);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("Failed to create Vulkan surface");
  }
  vk_surface_ = vk::SurfaceKHR(c_surface);

  spdlog::trace("Vulkan surface created");
}

void Context::select_vulkan_physical_device_() {
  vkb::PhysicalDeviceSelector selector{vkb_instance_, vk_surface_};
  auto select_result = selector.select();

  if (!select_result) {
    const auto& error = select_result.error();
    throw std::runtime_error(fmt::format("Failed to select physical device: {}", error.message()));
  }

  vkb_physical_device_ = select_result.value();
  vk_physical_device_ = vkb_physical_device_.physical_device;

  spdlog::trace("Vulkan physical device created");
}

void Context::create_vulkan_device_() {
  vkb::DeviceBuilder device_builder{vkb_physical_device_};
  auto device_result = device_builder.build();

  if (!device_result) {
    throw std::runtime_error("Failed to create logical device");
  }

  vkb_device_ = device_result.value();
  vk_device_ = vkb_device_.device;

  spdlog::trace("Vulkan device created");
}

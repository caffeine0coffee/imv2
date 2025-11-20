#include "src/core/render_context.hpp"

#include <memory>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

std::atomic<bool> Context::initialized_{false};
std::mutex Context::instance_mutex_;
std::unique_ptr<Context> Context::instance_ = nullptr;

void Context::Init(vk::SurfaceKHR vk_surface) {
  if (initialized_.exchange(true)) {
    spdlog::warn("Context::Init() called more than once");
    return;
  }

  std::lock_guard<std::mutex> lock(instance_mutex_);
  assert(instance_ == nullptr && "Context instance already exists");

  instance_ = std::unique_ptr<Context>(new Context(vk_surface));
}

const Context* Context::Instance() {
  if (!initialized_) {
    throw std::runtime_error("Context::Instance() called before Context::Init()");
  }

  std::lock_guard<std::mutex> lock(instance_mutex_);
  return instance_.get();
}

void Context::init_(vk::SurfaceKHR vk_surface) {
  create_vulkan_instance_();
  create_glfw_window_();
  select_vulkan_physical_device_(vk_surface);
  create_vulkan_device_();
}

void Context::destroy_() {
  vkb::destroy_device(vkb_device_);
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

void Context::select_vulkan_physical_device_(vk::SurfaceKHR vk_surface) {
  vkb::PhysicalDeviceSelector selector{vkb_instance_, vk_surface};
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

#include "src/core/renderer.hpp"

#include <memory>

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <VkBootstrap.h>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

void Renderer::Context::init_vulkan_instance() {
  if (is_instance_initialized_.exchange(true)) {
    spdlog::warn("Context::init_vulkan_instance() called more than once.");
    return;
  }

  vkb::InstanceBuilder builder;
  auto build_result = builder.set_app_name("imv2")
                          .request_validation_layers(true)
                          .require_api_version(1, 3, 0)
                          .build();
  if (!build_result) {
    const auto& error = build_result.error();
    throw std::runtime_error(fmt::format("Failed to create Vulkan instance: {}.", error.message()));
  }

  vkb_instance_ = build_result.value();
  vk_instance_ = vkb_instance_.instance;

  is_instance_initialized_ = true;

  spdlog::trace("Vulkan instance created.");
}

void Renderer::Context::init_vulkan_device(VkSurfaceKHR vk_surface) {
  if (is_device_initialized_.exchange(true)) {
    spdlog::warn("Context::init_vulkan_device() called more than once.");
    return;
  }
  if (!is_instance_initialized_) {
    throw std::runtime_error(
        "Vulkan instance must be initialized before initializing Vulkan device."
        "Call init_vulkan_instance() first.");
  }

  vkb::PhysicalDeviceSelector selector{vkb_instance_, vk_surface};
  auto select_result = selector.select();

  if (!select_result) {
    const auto& error = select_result.error();
    throw std::runtime_error(fmt::format("Failed to select physical device: {}.", error.message()));
  }

  vkb_physical_device_ = select_result.value();
  vk_physical_device_ = vkb_physical_device_.physical_device;

  spdlog::trace("Vulkan physical device selected.");

  vkb::DeviceBuilder device_builder{vkb_physical_device_};
  auto device_result = device_builder.build();

  if (!device_result) {
    throw std::runtime_error("Failed to create logical device.");
  }

  vkb_device_ = device_result.value();
  vk_device_ = vkb_device_.device;

  is_device_initialized_ = true;

  spdlog::trace("Vulkan device created.");
}

vk::Instance Renderer::Context::vk_instance() const {
  if (!is_instance_initialized_) {
    throw std::runtime_error(
        "Vulkan instance is not initialized. Call init_vulkan_instance() first.");
  }
  return vk_instance_;
}

vk::PhysicalDevice Renderer::Context::vk_physical_device() const {
  if (!is_device_initialized_) {
    throw std::runtime_error("Vulkan device is not initialized. Call init_vulkan_device() first.");
  }
  return vk_physical_device_;
}

vk::Device Renderer::Context::vk_device() const {
  if (!is_device_initialized_) {
    throw std::runtime_error("Vulkan device is not initialized. Call init_vulkan_device() first.");
  }
  return vk_device_;
}

void Renderer::Context::destroy_() {
  vkb::destroy_device(vkb_device_);
  spdlog::trace("Vulkan device destroyed.");

  vkb::destroy_instance(vkb_instance_);
  spdlog::trace("Vulkan instance destroyed.");
}

void Renderer::InitVulkanInstance() { Renderer::Instance()->context_->init_vulkan_instance(); }

void Renderer::InitVulkanDevice(vk::SurfaceKHR vk_surface) {
  Renderer::Instance()->context_->init_vulkan_device(static_cast<VkSurfaceKHR>(vk_surface));
}

Renderer* Renderer::Instance() {
  static Renderer instance;
  return &instance;
}

void Renderer::draw() {
  const auto vk_instance = context_->vk_instance();  // NOLINT
  const auto vk_device = context_->vk_device();  // NOLINT

  spdlog::info("Renderer::draw() called.");
}

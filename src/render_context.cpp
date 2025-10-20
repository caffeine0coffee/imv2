#include "src/render_context.hpp"

#include <VkBootstrap.h>
#include <spdlog/spdlog.h>

const Context* Context::Instance() {
  static Context instance;
  return &instance;
}

void Context::init_() {
  vkb::InstanceBuilder builder;
  auto build_result = builder.set_app_name("imv2")
                          .request_validation_layers(true)
                          .require_api_version(1, 4, 0)
                          .build();
  if (!build_result) {
    throw std::runtime_error("Failed to create Vulkan instance");
  }

  vk_instance_ = build_result.value();
  spdlog::trace("Vulkan instance created");

  // TODO(caffeine): create PhysicalDevice, Device, etc...
}

void Context::destroy_() {
  vk_instance_.destroy();
  spdlog::trace("Vulkan instance destroyed");
}

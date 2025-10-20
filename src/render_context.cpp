#include "src/render_context.hpp"

#include <VkBootstrap.h>

#include <memory>
#include <mutex>

std::mutex Context::instance_mutex_{};
std::unique_ptr<Context> Context::instance_{};

const Context* Context::Instance() {
  const auto lock = std::lock_guard(instance_mutex_);

  if (instance_ == nullptr) {
    instance_ = std::unique_ptr<Context>(new Context());
  }
  return instance_.get();
}

Context::Context() {
  vkb::InstanceBuilder builder;
  auto build_result = builder.set_app_name("imv2")
                          .request_validation_layers(true)
                          .require_api_version(1, 4, 0)
                          .build();
  if (!build_result) {
    throw std::runtime_error("Failed to create Vulkan instance");
  }

  vk_instance_ = build_result.value();

  // TODO(caffeine): create PhysicalDevice, Device, etc...
}

#include <spdlog/spdlog.h>

#include "src/render_context.hpp"

#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main() {
  uint32_t count = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
  std::vector<VkExtensionProperties> exts(count);
  vkEnumerateInstanceExtensionProperties(nullptr, &count, exts.data());

  for (auto& e : exts) std::cout << e.extensionName << "\n";
  spdlog::info("Hello, World!");

#ifdef DEBUG
  spdlog::set_level(spdlog::level::trace);
#endif

  const auto* const context = Context::Instance();
  const auto& vk_instance = context->vk_instance();
  spdlog::info("Context created!!!");

  return 0;
}

#pragma once

#include <memory>
#include <mutex>
#include <vulkan/vulkan.hpp>

class Context {
 public:
  static const Context* Instance();

  [[nodiscard]] const vk::Instance& vk_instance() const { return vk_instance_; }

 private:
  static std::mutex instance_mutex_;
  static std::unique_ptr<Context> instance_;

  Context();

  vk::Instance vk_instance_;
};

#pragma once

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

  vk::Instance vk_instance_;
};

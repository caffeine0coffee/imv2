cmake_minimum_required(VERSION 3.20)
project(imv2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE imv_sources src/*.cpp)
add_executable(imv2 ${imv_sources})
target_include_directories(imv2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(imv2 PRIVATE spdlog::spdlog)

find_package(vk-bootstrap CONFIG REQUIRED)
target_link_libraries(imv2 PRIVATE vk-bootstrap::vk-bootstrap vk-bootstrap::vk-bootstrap-compiler-warnings)

find_package(Vulkan REQUIRED)
target_link_libraries(imv2 PRIVATE Vulkan::Vulkan)

cmake_minimum_required(VERSION 3.20)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if (NOT LINUX)
    list(APPEND VCPKG_MANIFEST_FEATURES "build-with-vcpkg-vulkan")
endif ()
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.3" CACHE STRING "MacOS Deployment target")

project(imv2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

file(GLOB_RECURSE imv_sources src/*.cpp)
add_executable(imv2 ${imv_sources})
target_include_directories(imv2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(spdlog REQUIRED)
target_link_libraries(imv2 PRIVATE spdlog::spdlog)

find_package(vk-bootstrap REQUIRED)
target_link_libraries(imv2 PRIVATE vk-bootstrap::vk-bootstrap)

find_package(Vulkan REQUIRED)
target_link_libraries(imv2 PRIVATE Vulkan::Vulkan)

find_package(glfw3 REQUIRED)
target_link_libraries(imv2 PRIVATE glfw)

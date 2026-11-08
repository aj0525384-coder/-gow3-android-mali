
cmake_minimum_required(VERSION 3.22.1)

project(gow3_mali_diagnostic LANGUAGES CXX)

add_library(
    gow3_gpu
    SHARED
    vulkan_probe.cpp
)

find_library(
    vulkan-lib
    vulkan
)

target_link_libraries(
    gow3_gpu
    ${vulkan-lib}
)

target_compile_features(
    gow3_gpu
    PRIVATE cxx_std_17
)

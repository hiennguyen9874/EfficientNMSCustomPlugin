cmake_minimum_required(VERSION 3.22)

project(EfficientNMSCustomPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES OR CMAKE_CUDA_ARCHITECTURES STREQUAL "")
    set(CMAKE_CUDA_ARCHITECTURES 75 CACHE STRING "CUDA architectures" FORCE)
endif()

enable_language(CUDA)

option(BUILD_PLUGIN_REGISTRY_CHECK_APP "Build minimal plugin registry check app" ON)

set(TENSORRT_ROOT "$ENV{TENSORRT_ROOT}" CACHE PATH "TensorRT install root (contains include/ and lib/)" )
set(TENSORRT_OSS_ROOT "$ENV{TENSORRT_OSS_ROOT}" CACHE PATH "TensorRT OSS source root (contains plugin/common)")

if(NOT TENSORRT_ROOT)
    set(TENSORRT_ROOT "/usr")
endif()

set(TENSORRT_INCLUDE_DIR "${TENSORRT_ROOT}/include" CACHE PATH "TensorRT include directory")
set(TENSORRT_LIBRARY_DIR "${TENSORRT_ROOT}/lib" CACHE PATH "TensorRT library directory")
if(EXISTS "/usr/lib/x86_64-linux-gnu")
    list(APPEND CMAKE_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu")
endif()
list(APPEND CMAKE_LIBRARY_PATH "${TENSORRT_LIBRARY_DIR}")

find_package(CUDAToolkit REQUIRED)
find_library(NVINFER_LIB nvinfer REQUIRED)
find_library(NVINFER_PLUGIN_LIB nvinfer_plugin REQUIRED)

add_subdirectory(src)

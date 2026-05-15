# EfficientNMSCustom Plugin Build & Load Example

This repository now includes a standalone CMake build for `src/plugins/efficientNMSCustom` and a minimal runtime checker app.

## What it builds

- Plugin shared library:
  - `build/src/plugins/efficientNMSCustom/libefficient_nms_custom.so`
- Minimal checker executable:
  - `build/src/apps/plugin_registry_check/check_efficient_nms_plugin`

The checker loads the plugin `.so` with `dlopen()` and verifies the TensorRT plugin creator is registered:

- name: `EfficientNMSCustom_TRT`
- version: `1`

## Requirements

- CMake >= 3.22
- CUDA Toolkit (with `nvcc`)
- TensorRT installed (headers + libs)
- TensorRT OSS source tree (for `plugin/common` headers used by this plugin)

## Configure

```bash
cmake -S . -B build \
  -DCMAKE_CUDA_COMPILER=/usr/local/cuda-12.1/bin/nvcc \
  -DTENSORRT_ROOT=/usr \
  -DTENSORRT_OSS_ROOT=/home/jovyan/workspace/TensorRT
```

Notes:

- `TENSORRT_ROOT` should contain `include/` and `lib/`.
- `TENSORRT_OSS_ROOT` should contain `plugin/common/plugin.h`.

## Build

```bash
cmake --build build -j
```

## Run plugin registration check

```bash
./build/src/apps/plugin_registry_check/check_efficient_nms_plugin \
  ./build/src/plugins/efficientNMSCustom/libefficient_nms_custom.so
```

Expected output:

```text
Plugin creator found: EfficientNMSCustom_TRT v1
```

## CMake options

- `BUILD_PLUGIN_REGISTRY_CHECK_APP=ON|OFF` (default `ON`)
  - Build or skip the checker executable.

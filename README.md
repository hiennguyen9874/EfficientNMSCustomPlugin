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
- TensorRT OSS `plugin/common` headers (vendored in this repo under `third_party/tensorrt_oss`) or an external TensorRT OSS source tree

## Configure

```bash
cmake -S . -B build \
  -DCMAKE_CUDA_COMPILER=/usr/local/cuda-12.1/bin/nvcc \
  -DTENSORRT_ROOT=/usr
```

Notes:

- `TENSORRT_ROOT` should contain `include/` and `lib/`.
- By default, `TENSORRT_OSS_ROOT` uses the vendored path `third_party/tensorrt_oss`.
- You can override with `-DTENSORRT_OSS_ROOT=/path/to/TensorRT` (must contain `plugin/common/plugin.h`).

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

# Build System Instructions

## Read When

- You modify `CMakeLists.txt` files.
- You change plugin compile/link options or TensorRT/CUDA path handling.
- You need exact configure/build/run commands.

## Purpose

Provide file-grounded build and runtime-check commands for this repository.

## Rules

- Build is CMake-based from repo root (`CMakeLists.txt`).
- CUDA language is enabled and expected (`enable_language(CUDA)`).
- `TENSORRT_ROOT` must provide `include/` and `lib/`.
- `TENSORRT_OSS_ROOT` must provide `plugin/common/plugin.h`; configure fails if missing.
- Keep `BUILD_PLUGIN_REGISTRY_CHECK_APP` behavior intact unless task explicitly changes it.

## Commands

- Configure:
  - `cmake -S . -B build -DCMAKE_CUDA_COMPILER=/usr/local/cuda-12.1/bin/nvcc -DTENSORRT_ROOT=/usr -DTENSORRT_OSS_ROOT=/home/jovyan/workspace/TensorRT`
- Build:
  - `cmake --build build -j`
- Run registry checker:
  - `./build/src/apps/plugin_registry_check/check_efficient_nms_plugin ./build/src/plugins/efficientNMSCustom/libefficient_nms_custom.so`

## Key Paths

- Root build config: `CMakeLists.txt`
- Plugin target config: `src/plugins/efficientNMSCustom/CMakeLists.txt`
- Checker app config: `src/apps/plugin_registry_check/CMakeLists.txt`

## Gotchas

- `src/plugins/efficientNMSCustom/CMakeLists.txt` hard-fails when TensorRT OSS headers are not found.
- Checker executable exists only when `BUILD_PLUGIN_REGISTRY_CHECK_APP=ON` (default ON).

## Related Instructions

- `docs/agent-instructions/architecture.md`
- `docs/agent-instructions/development-workflow.md`

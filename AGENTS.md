# EfficientNMSCustomPlugin Agent Guide

Standalone TensorRT plugin build for `EfficientNMSCustom` plus a minimal runtime registry check app.

## Quick Commands

- Configure:
  - `cmake -S . -B build -DCMAKE_CUDA_COMPILER=/usr/local/cuda-12.1/bin/nvcc -DTENSORRT_ROOT=/usr`
  - Optional override: `-DTENSORRT_OSS_ROOT=/path/to/TensorRT`
- Build:
  - `cmake --build build -j`
- Run plugin registry check:
  - `./build/src/apps/plugin_registry_check/check_efficient_nms_plugin ./build/src/plugins/efficientNMSCustom/libefficient_nms_custom.so`

## Mini Repo Map

- `src/plugins/efficientNMSCustom/` — plugin sources, CUDA kernels, plugin docs
- `src/apps/plugin_registry_check/` — small executable that `dlopen()`s plugin and checks creator registration
- `src/**/CMakeLists.txt` — build graph for plugin and optional checker app
- `weights/` — model artifacts (not part of build logic)

## Instruction Index

Read these only when task matches scope:

| File | Read when | Contains |
|---|---|---|
| `docs/agent-instructions/build-system.md` | You change build config, dependency paths, or compile/link behavior | Required toolchain inputs, CMake options, and build/run workflow |
| `docs/agent-instructions/architecture.md` | You change plugin/app boundaries, runtime loading, or TensorRT integration points | Component responsibilities and runtime flow |
| `docs/agent-instructions/development-workflow.md` | You implement code changes and need validation expectations | Change-scope rules and practical verification steps |

## Critical Rules

- Keep root instructions concise; place detail under `docs/agent-instructions/`.
- Do not invent commands, dependencies, or runtime assumptions not present in repo files.
- Keep changes surgical: touch only files needed for the requested task.
- Prefer focused checks near changed code; there is no project-wide test suite defined in this repo.

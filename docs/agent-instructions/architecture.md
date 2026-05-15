# Architecture Instructions

## Read When

- You change plugin internals, plugin registration behavior, or runtime loading flow.
- You alter boundaries between plugin library and checker app.

## Purpose

Describe component responsibilities and the runtime integration path.

## Component Map

- Plugin library target: `efficient_nms_custom`
  - Defined in `src/plugins/efficientNMSCustom/CMakeLists.txt`
  - Sources: `src/plugins/efficientNMSCustom/*.cpp` and `*.cu`
  - Links against TensorRT (`nvinfer`, `nvinfer_plugin`) and CUDA runtime
- Runtime checker app: `check_efficient_nms_plugin`
  - Defined in `src/apps/plugin_registry_check/CMakeLists.txt`
  - Loads plugin `.so` via `dlopen()` and checks TensorRT plugin creator registration

## Runtime Flow

1. Build shared library `libefficient_nms_custom.so`.
2. Run checker executable with plugin `.so` path.
3. Checker loads library and verifies creator:
   - name: `EfficientNMSCustom_TRT`
   - version: `1`

## Rules

- Preserve plugin creator name/version contract unless task explicitly changes compatibility.
- Keep plugin source locality in `src/plugins/efficientNMSCustom/`; avoid cross-cutting moves unless required.
- Keep checker app minimal and focused on registration verification.

## Key Paths

- `src/plugins/efficientNMSCustom/`
- `src/apps/plugin_registry_check/main.cpp`
- `src/CMakeLists.txt`

## Related Instructions

- `docs/agent-instructions/build-system.md`
- `docs/agent-instructions/development-workflow.md`

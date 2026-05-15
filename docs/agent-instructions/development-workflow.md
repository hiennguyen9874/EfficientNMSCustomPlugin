# Development Workflow Instructions

## Read When

- You are implementing code changes and need repo-specific execution/validation expectations.

## Purpose

Keep changes small, verifiable, and aligned with this repo’s current tooling.

## Rules

- Use minimal edits and preserve current CMake/source structure.
- Do not add dependencies unless explicitly required by the task.
- Validate with the narrowest relevant command first.
- If build/validation cannot run due to missing local TensorRT/CUDA setup, state the blocker clearly.

## Verification Strategy

1. CMake changes or source changes that affect build graph:
   - verify: `cmake -S . -B build ...` succeeds.
2. Plugin or checker code changes:
   - verify: `cmake --build build -j` succeeds.
3. Registration-path changes:
   - verify: checker reports `Plugin creator found: EfficientNMSCustom_TRT v1`.

## Known Limits

- No unit/integration test framework is defined in repo files.
- Primary validation path is configure/build/checker execution.

## Related Instructions

- `docs/agent-instructions/build-system.md`
- `docs/agent-instructions/architecture.md`

# Memory Corruption Lab (C++)

This repository demonstrates common memory safety issues in C/C++ using small practical examples.

## Topics covered

- Stack overflow
- Heap overflow
- Use-after-free (UAF)
- Heap allocation reuse / heap shaping
- Detection with AddressSanitizer (ASAN)
- Debugging with LLDB

## Files

- `stack_overflow.cpp` — demonstrates stack-based buffer overflow and control-flow corruption
- `heap_overflow.cpp` — demonstrates corruption of adjacent heap allocation
- `uaf_demo.cpp` — demonstrates use-after-free and dangling pointer behavior
- `heap_control.cpp` — demonstrates heap reuse / heap shaping

## Key observations

### Stack overflow
- Writing past a local stack buffer can corrupt control-flow-related data
- Crash may happen only when the function returns
- Debugging showed invalid jump to an address derived from attacker-controlled input

### Heap overflow
- Adjacent heap allocations can be silently corrupted
- Overflow does not always crash immediately
- Corruption may affect meaningful application data

### Use-after-free
- Freed memory may be reused by allocator
- Dangling pointers can still reference that memory
- Reused memory may contain attacker-controlled data

### Heap shaping
- Allocation and free order influences memory reuse
- Specific objects can be placed in targeted heap locations

## ASAN
AddressSanitizer was used to detect:
- heap-buffer-overflow
- heap-use-after-free

## Why this matters
These examples show how memory corruption bugs behave in practice and how runtime tooling helps detect them early during development.
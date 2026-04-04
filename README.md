# Memory Corruption Lab (C++)

## Overview
This repository contains practical examples of common memory corruption vulnerabilities in C/C++, along with debugging techniques and secure fixes.

It is designed as a hands-on lab to understand both exploitation concepts and defensive programming practices.

## Topics covered

- Stack overflow
- Heap overflow
- Use-after-free (UAF)
- Heap allocation reuse / heap shaping
- Integer overflow
- Detection with AddressSanitizer (ASAN)
- Debugging with LLDB

## How to build and run

### Normal build
clang++ -g -O0 heap_overflow.cpp -o heap_overflow
./heap_overflow

## With AddressSanitizer
clang++ -fsanitize=address -g -O0 heap_overflow.cpp -o heap_overflow_asan 
./heap_overflow_asan

## Files

- `stack_overflow.cpp` — demonstrates stack-based buffer overflow and control-flow corruption
- `heap_overflow.cpp` — demonstrates and analyzes corruption of adjacent heap allocation
- `uaf_demo.cpp` — demonstrates use-after-free and dangling pointer behavior
- `heap_control.cpp` — demonstrates heap reuse / heap shaping
- `integer_overflow.cpp` - demonstrates overflow in allocation size calculation

## Key observations

## Security Learning Outcomes

- Understanding how memory corruption occurs in real programs
- Identifying silent corruption vs crash-based bugs
- Recognizing dangerous patterns like dangling pointers
- Using runtime tools (ASAN) to detect vulnerabilities early
- Understanding how attackers can influence memory layout (heap shaping)

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

### Integer overflow
- Arithmetic overflow during size calculation can result in incorrect memory allocation
- Multiplication like `count * sizeof(int)` may wrap around if input is too large
- Overflow can produce undersized allocations (e.g., 0 bytes)
- It can silently break memory allocation logic and lead to serious vulnerabilities like heap overflow.

## ASAN
AddressSanitizer was used to detect:
- heap-buffer-overflow
- heap-use-after-free
- out-of-bounds memory access

### Example (heap overflow)

clang++ -fsanitize=address -g -O0 heap_overflow.cpp -o heap_overflow_asan
./heap_overflow_asan

### Sample output

heap_overflow_asan(36915,0x1f9c3e240) malloc: nano zone abandoned due to inability to reserve vm space.

Address of a: 0x6020000000b0

Address of b: 0x6020000000d0

Distance: 32



Before overflow: 

b: BBBBBBBBBBBBBBB

=================================================================

==36915==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6020000000c0 at pc 0x000102c971a8 bp 0x00016dacf2e0 sp 0x00016dacea90

WRITE of size 38 at 0x6020000000c0 thread T0

    #0 0x000102c971a4 in strcpy+0x458 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x371a4)

    #1 0x000102330970 in main heap_overflow.cpp:21

    #2 0x00018b906b94  (<unknown module>)



0x6020000000c0 is located 0 bytes after 16-byte region [0x6020000000b0,0x6020000000c0)

allocated by thread T0 here:

    #0 0x000102c9d30c in malloc+0x78 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x3d30c)

    #1 0x000102330888 in main heap_overflow.cpp:7

    #2 0x00018b906b94  (<unknown module>)




SUMMARY: AddressSanitizer: heap-buffer-overflow heap_overflow.cpp:21 in main

### Example (use-after-free)

clang++ -fsanitize=address -g -O0 uaf_demo.cpp -o uaf_asan
./uaf_asan

### Sample output

Before free: HELLO

=================================================================

==37105==ERROR: AddressSanitizer: heap-use-after-free on address 0x6020000000b0 at pc 0x00010356a918 bp 0x00016cf43290 sp 0x00016cf42a50

READ of size 2 at 0x6020000000b0 thread T0

    #0 0x00010356a914 in strlen+0x1b4 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x7a914)

    #1 0x000102ebe598 in unsigned long std::__1::__constexpr_strlen[abi:ne200100]<char>(char const*) constexpr_c_functions.h:63

    #2 0x000102ebd1c0 in std::__1::char_traits<char>::length[abi:ne200100](char const*) char_traits.h:232

    #3 0x000102ebc94c in std::__1::basic_ostream<char, std::__1::char_traits<char>>& std::__1::operator<<[abi:ne200100]<std::__1::char_traits<char>>(std::__1::basic_ostream<char, std::__1::char_traits<char>>&, char const*) basic_ostream.h:435

    #4 0x000102ebc908 in main uaf_demo.cpp:19

    #5 0x00018b906b94  (<unknown module>)



0x6020000000b0 is located 0 bytes inside of 16-byte region [0x6020000000b0,0x6020000000c0)

freed by thread T0 here:

    #0 0x00010352d400 in free+0x7c (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x3d400)

    #1 0x000102ebc8d4 in main uaf_demo.cpp:12

    #2 0x00018b906b94  (<unknown module>)



previously allocated by thread T0 here:

    #0 0x00010352d30c in malloc+0x78 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x3d30c)

    #1 0x000102ebc888 in main uaf_demo.cpp:7

    #2 0x00018b906b94  (<unknown module>)




SUMMARY: AddressSanitizer: heap-use-after-free constexpr_c_functions.h:63 in unsigned long std::__1::__constexpr_strlen[abi:ne200100]<char>(char const*)

ASAN provides:
- precise error detection(heap-buffer-overflow, use-after-free,  out-of-bounds access)
- memory access tracking
- immediate program termination on invalid access

## Debugging with LLDB

LLDB was used for low-level debugging and crash analysis.

### Example (stack overflow)

lldb ./stack_overflow
run

### Inspecting crash

bt

### Sample output

(lldb) run
Process 35470 launched: '/stack_overflow'

address of buffer: 0x16fdff140

address of marker: 0x16fdff13c

enter input: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Buffer: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

Marker: 12345

Process 35470 stopped

* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=257, address=0x4141414141414141)

    frame #0: 0x0000414141414141

error: memory read failed for 0x414141414000

Target 0: (stack_overflow) stopped.

(lldb) bt

* thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=257, address=0x4141414141414141)

  * frame #0: 0x0000414141414141

(lldb) 


### Observations

- Crash occurs during function return
- Instruction pointer is corrupted
- Program attempts to jump to invalid memory (e.g., 0x4141414141414141)

LLDB helps in:
- inspecting stack frames
- identifying control flow corruption/invalid memory access
- analyzing crash behavior

## Why this matters
These examples show how memory corruption bugs behave in practice and how runtime tooling helps detect them early during development.

## Fixed Implementations

Each vulnerability has a corresponding fixed version demonstrating safer coding practices.

- `stack_overflow_fixed.cpp`
- Uses `std::string` instead of fixed-size buffers
- Enforces input length checks

- `heap_overflow_fixed.cpp`
- Uses bounded writes (`snprintf`)
- Prevents overwriting adjacent memory

- `heap_overflow_fixed_input.cpp`
- Uses safe input handling (`fgets`)
- Avoids uncontrolled user input overflow

- `uaf_demo_fixed.cpp`
- Avoids accessing memory after `free`
- Invalidates pointer using `nullptr`

- `uaf_demo_smart_ptr.cpp`
- Uses `std::unique_ptr` for automatic memory management
- Demonstrates safer ownership model

- `integer_overflow_fixed.cpp`
- validate allocation size to prevent integer overflow during multiplication

## Mitigation Strategies

Key defensive techniques demonstrated in this lab:

- enforce strict bounds checking on buffers
- use safer APIs (`fgets`, `snprintf`)
- avoid unsafe functions like `gets` and unchecked `strcpy`
- never access memory after it has been freed
- invalidate pointers after `free`
- prefer smart pointers in modern C++
- validate input sizes and prevent integer overflow during allocation
- use runtime tools like AddressSanitizer (ASAN)
- use debugging tools like LLDB for crash analysis

## Learning Outcomes

This lab demonstrates:

- how memory corruption vulnerabilities occur
- how they impact program behavior and security
- Understanding how integer overflow can lead to unsafe memory allocation
- how to detect them using modern tools
- how to fix them using safe coding practices
- how to apply defensive programming in C/C++


# cijs

A simple JS interpreter written in c

## Getting started

This guide will help you build, test, and run the CIJS interpreter.

### Prerequisites

- _C Compiler_: `clang`
- _CMake_: Version 3.10

### Clone the repository

```bash
git clone https://github.com/fbcarpinato/cijs
cd cijs
git submodule update --init --recursive
```

### Build

```bash
# Configure and build
cmake -S . -B build
cmake --build build

# Run the interpreter
./build/cijs
```

### Test

```bash
# Configure and build
cmake -S . -B build
cmake --build build

# Run the tests
./build/test_suite
```

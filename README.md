# boilerplate-grpc
This is my boilerplate code for C++ and gRPC in combination with
[vcpkg](https://github.com/microsoft/vcpkg) and CMake.

## Initialize build environment 

```bash
cmake -S . -B build --preset default
```

## Build app

```bash
cmake --build build
```

## Quickstart macOS

### CMake

```bash
brew install cmake pkg-config ninja
```
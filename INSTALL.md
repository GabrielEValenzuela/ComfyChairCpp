# Installing ComfyChair

## Prerequisites
- C++ Compiler (C++20 or later)
- CMake (Version 3.15 or later)
- Git

## Installation Steps
1. Clone the repository:

```console
git clone https://github.com/GabrielEValenzuela/ComfyChairCpp
```

2. Configure the project

```console
mkdir build && cd build
```
- You can use `Ninja`, in preference

```console
cmake -GNinja ..
```

- or `make`

```console
cmake ..
```

>[!NOTE]
> To run with test and coverage, run with `-DRUN_COVERAGE=1` in the configuration step.

3. Build and execute

```console
ninja or make -jNThreads
```

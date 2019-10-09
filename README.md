# CXXUtility

This library provides utility types, and preprocessor definitions and macros used in my projects.

# Building

Building this library is straight forward.

```bash
mkdir <build directory>
cd <build directory>
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<installation directory> <path to repository>
make -j<threads> -l<cores>
```

Afterwards install CXXUtility using `[sudo] make package`.

## Usage

CXXUtility exports it's targets and provides a CMake package. Therefore use `find_package(cxxutility REQUIRED)` to find the provided package and link it to your target.

cmake_minimum_required(VERSION 3.0.0)
project(elso VERSION 0.1.0)

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core C++ libraries
add_subdirectory(src/cpp/utils)

# Bindings libraries
add_subdirectory(src/bindings)

# Tests
add_subdirectory(tests/cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

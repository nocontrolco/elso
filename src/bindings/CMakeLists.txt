cmake_minimum_required(VERSION 3.0.0)
project(elso_bindings LANGUAGES CXX)

find_package(Python 3.10 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

add_definitions(-DPYBIND)
find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_DIRS})

# Create an extension module
add_library(
    elso_bindings
    MODULE
        elso_bindings.cpp
)
target_link_libraries(
    elso_bindings
    PUBLIC
        pybind11::module
    PRIVATE
        elso_utils
)

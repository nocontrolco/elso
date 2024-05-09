cmake_minimum_required(VERSION 3.0.0)
project(elso VERSION 0.1.0)

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
find_package(Boost REQUIRED)

include(CTest)
enable_testing()

# Tests
add_executable(test_assets test_assets.cpp)
target_link_libraries(test_assets PRIVATE elso_utils)

add_test(
    NAME test_assets
    COMMAND $<TARGET_FILE:test_assets>
)

add_executable(test_calculators test_calculators.cpp)
target_link_libraries(test_calculators PRIVATE elso_utils)

add_test(
    NAME test_calculators
    COMMAND $<TARGET_FILE:test_calculators>
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

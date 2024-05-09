cmake_minimum_required(VERSION 3.0.0)
project(elso VERSION 0.1.0)

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS date_time)

include(CTest)
enable_testing()

add_library(
    elso_utils
    SHARED

        # utils
        types.cpp
        types.hpp
        includes.hpp
        definitions.hpp
        math.hpp
)
target_link_libraries(elso_utils ${Boost_LIBRARIES})
target_compile_definitions(elso_utils PUBLIC elso_utils)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

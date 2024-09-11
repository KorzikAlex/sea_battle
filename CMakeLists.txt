cmake_minimum_required(VERSION 3.29)
project(sea_battle)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(src)

add_executable(sea_battle
        src/main.cpp)

add_compile_options(
        -fdiagnostics-color=always
        -pedantic-errors
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wduplicated-branches
        -Wextra-semi
        -Wenum-compare
        -Wfloat-equal
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
)

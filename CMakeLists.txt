cmake_minimum_required(VERSION 3.28)

project(sea_battle LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(src src)

set(main "sea_battle")

file(GLOB_RECURSE SOURCES_
        ${src}/*.cpp
)

include_directories("include")
include_directories(${json_SOURCE_DIR}/include)

add_library(sea_battle_lib
        ${SOURCES_}
)

add_compile_options(
        -fdiagnostics-color=always
        -pedantic-errors
        #        -Werror
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
        -Wnon-virtual-dtor
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
)

add_executable(${main} ${src}/main.cpp)

target_compile_features(${main} PRIVATE cxx_std_17)
target_link_libraries(${main} PRIVATE sea_battle_lib nlohmann_json::nlohmann_json)

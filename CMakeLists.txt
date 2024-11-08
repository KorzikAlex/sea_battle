cmake_minimum_required(VERSION 3.28)

project(sea_battle LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(main seabattle.out)
set(src src)
set(modules ${src}/modules)
set(abilities ${modules}/abilities)
set(ships ${modules}/ships)
set(exceptions ${src}/exceptions)

set(SOURCES ${src}/main.cpp ${src}/cli_parser.cpp ${modules}/board.cpp
        ${ships}/ship.cpp ${ships}/ship_manager.cpp
        ${abilities}/ability_manager.cpp ${abilities}/abilities_list.cpp
        ${exceptions}/invalid_ship_size.cpp)

include_directories("include")

add_library(sea_battle_lib ${SOURCES})

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

include(FetchContent)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/_deps/sfml-src")
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x
            GIT_SHALLOW ON
            EXCLUDE_FROM_ALL
            SYSTEM
    )
    FetchContent_MakeAvailable(SFML)
else ()
    message(STATUS "SFML sources already exist, skipping download.")
endif ()

add_executable(${main} ${SOURCES})

target_compile_features(${main} PRIVATE cxx_std_17)
target_link_libraries(${main} PRIVATE sea_battle_lib sfml-graphics)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    add_custom_target(COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
else (DOXYGEN_FOUND)
    MESSAGE(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
endif (DOXYGEN_FOUND)
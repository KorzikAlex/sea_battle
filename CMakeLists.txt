cmake_minimum_required(VERSION 3.28)

project(sea_battle LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(main sea_battle.out)
set(src src)
set(modules ${src}/modules)
set(abilities ${modules}/abilities)
set(ships ${modules}/ships)
set(exceptions ${src}/exceptions)

set(SOURCES_ ${src}/cli_parser.cpp ${modules}/board.cpp ${src}/game.cpp
        ${ships}/ship.cpp ${ships}/ship_manager.cpp
        ${abilities}/ability_manager.cpp ${abilities}/abilities_list.cpp
        )

set(EXCEPTIONS_ ${exceptions}/invalid_ship_size.cpp ${exceptions}/attack_out_of_range.cpp
        ${exceptions}/incorrect_ship_position.cpp ${exceptions}/no_available_abilities.cpp
        )

include_directories("include")

add_library(sea_battle_lib ${SOURCES_} ${EXCEPTIONS_})

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
target_link_libraries(${main} PRIVATE sea_battle_lib)

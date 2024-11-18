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
        ${abilities}/ability_manager.cpp ${abilities}/abilities_list.cpp)

set(EXCEPTIONS_ ${exceptions}/invalid_ship_size.cpp ${exceptions}/attack_out_of_range.cpp
        ${exceptions}/incorrect_ship_position.cpp ${exceptions}/no_available_abilities.cpp)

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

add_executable(${main} ${src}/main.cpp)

target_compile_features(${main} PRIVATE cxx_std_17)
target_link_libraries(${main} PRIVATE sea_battle_lib sfml-graphics)

#find_package(Doxygen)
#if (DOXYGEN_FOUND)
#    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
#    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
#    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
#    add_custom_target(doxygen ALL
#            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
#            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#            COMMENT "Generating documentation with Doxygen"
#            VERBATIM
#    )
#else (DOXYGEN_FOUND)
#    MESSAGE(STATUS "WARNING: Doxygen not found - Reference manual will not be created")
#endif (DOXYGEN_FOUND)

if (WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM)
endif ()
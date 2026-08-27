cmake_minimum_required(VERSION 3.28)

project(
    avernal-input
    VERSION 0.1.0
    DESCRIPTION "Keyboard and mouse input for the Avernal game engine"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(FetchContent)

set(AVERNAL_CORE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../avernal-core")

if(NOT EXISTS "${AVERNAL_CORE_SOURCE_DIR}/CMakeLists.txt")
    message(FATAL_ERROR
        "avernal-core not found at:\n"
        "  ${AVERNAL_CORE_SOURCE_DIR}\n"
        "Place avernal-core as a sibling of this project, or set "
        "FETCHCONTENT_SOURCE_DIR_AVERNAL_CORE.")
endif()

FetchContent_Declare(
    avernal_core
    SOURCE_DIR "${AVERNAL_CORE_SOURCE_DIR}"
    EXCLUDE_FROM_ALL
)

set(AVERNAL_CORE_BUILD_DEMO OFF)

FetchContent_MakeAvailable(avernal_core)

add_library(avernal-input)
add_library(avernal::input ALIAS avernal-input)

target_sources(
    avernal-input
    PRIVATE src/input.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS include
        FILES
            include/avernal/input/input.hpp
            include/avernal/input/keys.hpp
)

target_link_libraries(avernal-input PUBLIC avernal::core)
target_compile_features(avernal-input PUBLIC cxx_std_23)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(avernal-input PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(avernal-input PRIVATE /W4)
endif()

option(AVERNAL_INPUT_BUILD_DEMO "Build the Avernal Input demo executable" ON)

if(AVERNAL_INPUT_BUILD_DEMO)
    add_executable(avernal-input-demo apps/demo/main.cpp)
    target_link_libraries(avernal-input-demo PRIVATE avernal::input)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(avernal-input-demo PRIVATE -Wall -Wextra -Wpedantic)
    elseif(MSVC)
        target_compile_options(avernal-input-demo PRIVATE /W4)
    endif()
endif()

if(PROJECT_IS_TOP_LEVEL)
    option(AVERNAL_INPUT_BUILD_TESTS "Build Avernal Input unit tests" ON)
else()
    option(AVERNAL_INPUT_BUILD_TESTS "Build Avernal Input unit tests" OFF)
endif()

if(AVERNAL_INPUT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(GEODE_DISABLE_PRECOMPILED_HEADERS ON)
set(ICON_RANDOMIZER_TESTING OFF)

project(IconRandomizerAPI VERSION 2.2.0)

add_library(${PROJECT_NAME} SHARED
    src/IconRandomizer.cpp
)

if (ICON_RANDOMIZER_TESTING)
    target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)

if (PROJECT_IS_TOP_LEVEL)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ICON_RANDOMIZER_API_EXPORTING)
endif()

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

setup_geode_mod(${PROJECT_NAME})

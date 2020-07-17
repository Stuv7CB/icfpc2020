cmake_minimum_required(VERSION 3.12)

project(icfpc2020 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Starting collecting dependencies")

add_subdirectory("${CMAKE_SOURCE_DIR}/cpp-httplib" "${CMAKE_BINARY_DIR}/cpp-httplib-bin" EXCLUDE_FROM_ALL)

message(STATUS "Collecting project files")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")

if(DEFINED USE_GTEST AND USE_GTEST)
    enable_testing()
    message(STATUS "Starting collecting dependencies")
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("${CMAKE_SOURCE_DIR}/googletest" "${CMAKE_BINARY_DIR}/googletest-bin" EXCLUDE_FROM_ALL)
    message(STATUS "Collecting test files")
    add_subdirectory("${CMAKE_SOURCE_DIR}/tests")
    add_test(NAME tests COMMAND tests)
endif()

cmake_minimum_required(VERSION 3.12)

project(icfpc2020 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

message(STATUS "Starting collecting dependencies")

add_subdirectory("${CMAKE_SOURCE_DIR}/cpp-httplib" "${CMAKE_BINARY_DIR}/cpp-httplib-bin")

message(STATUS "Collecting project files")

add_subdirectory("${CMAKE_SOURCE_DIR}/src")

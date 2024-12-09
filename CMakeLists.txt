cmake_minimum_required(VERSION 3.20)

project(
  AOC2024
  VERSION 1.0
  DESCRIPTION "Advent of Code 2024"
  LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

set(CURRENT_DATE 10)
add_subdirectory(src)
add_subdirectory(apps)

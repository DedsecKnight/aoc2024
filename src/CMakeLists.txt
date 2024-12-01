set(HEADER_LIST "${AOC2024_SOURCE_DIR}/include/aoc2024/sol.hpp")

foreach(d RANGE 1 "${CURRENT_DATE}")
  add_library("d${d}p1" "day${d}/part01.cpp")
  target_include_directories("d${d}p1" PUBLIC "${AOC2024_SOURCE_DIR}/include/")
  target_compile_features("d${d}p1" PUBLIC cxx_std_17)

  add_library("d${d}p2" "day${d}/part02.cpp")
  target_include_directories("d${d}p2" PUBLIC "${AOC2024_SOURCE_DIR}/include/")
  target_compile_features("d${d}p2" PUBLIC cxx_std_17)
endforeach()

add_library(p1 "day${CURRENT_DATE}/part01.cpp")
target_include_directories(p1 PUBLIC "${AOC2024_SOURCE_DIR}/include/")
target_compile_features(p1 PUBLIC cxx_std_17)

add_library(p2 "day${CURRENT_DATE}/part02.cpp")
target_include_directories(p2 PUBLIC "${AOC2024_SOURCE_DIR}/include/")
target_compile_features(p2 PUBLIC cxx_std_17)

source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})

add_executable(part1 main.cpp)
target_compile_features(part1 PRIVATE cxx_std_17)
target_link_libraries(part1 PRIVATE p1)

add_executable(part2 main.cpp)
target_compile_features(part2 PRIVATE cxx_std_17)
target_link_libraries(part2 PRIVATE p2)

foreach(d RANGE 1 "${CURRENT_DATE}")
  add_executable("day${d}part1" main.cpp)
  target_compile_features("day${d}part1" PRIVATE cxx_std_17)
  target_link_libraries("day${d}part1" PRIVATE "d${d}p1")

  add_executable("day${d}part2" main.cpp)
  target_compile_features("day${d}part2" PRIVATE cxx_std_17)
  target_link_libraries("day${d}part2" PRIVATE "d${d}p2")
endforeach()

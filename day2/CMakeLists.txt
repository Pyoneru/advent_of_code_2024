project(Day2)


add_executable(Day2 main.cpp)
target_include_directories(Day2 PRIVATE ../tool/include)
target_link_libraries(Day2 PRIVATE fmt::fmt Tool)


file(COPY ${CMAKE_SOURCE_DIR}/day2/input.txt DESTINATION ${CMAKE_BINARY_DIR}/day2)
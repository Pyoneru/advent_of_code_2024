
project(Day1)

set(CMAKE_CXX_STANDARD 20)


add_executable(Day1 main.cpp)
target_link_libraries(Day1 PRIVATE fmt::fmt Tool)
target_include_directories(Day1 PRIVATE ../tool/include)


file(COPY ${CMAKE_SOURCE_DIR}/day1/input.txt DESTINATION ${CMAKE_BINARY_DIR}/day1)
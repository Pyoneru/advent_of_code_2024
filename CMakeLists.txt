cmake_minimum_required(VERSION 3.29)
project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 20)


include(FetchContent)
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_subdirectory(tool)
add_subdirectory(day1)
add_subdirectory(day2)

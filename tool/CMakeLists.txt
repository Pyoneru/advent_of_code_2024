project(Tool)

set(CMAKE_CXX_STANDARD 20)


add_library(Tool include/strings.hpp src/strings.cpp)
target_link_libraries(Tool PRIVATE fmt::fmt)
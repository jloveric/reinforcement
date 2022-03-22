cmake_minimum_required(VERSION 3.18)

project(reinforce)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRC
     "include/*.hh"
     "source/*.cpp"
)
add_executable(reinforce "${SRC}")

#add_library(lib source/*.cpp)


target_include_directories(reinforce PUBLIC include)

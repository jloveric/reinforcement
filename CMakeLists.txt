cmake_minimum_required(VERSION 3.18)

project(reinforce)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB SRC
     "include/*.hh"
     "source/*.cpp"
)
add_subdirectory(tests)

add_executable(reinforce "${SRC}")
target_include_directories(reinforce PUBLIC include)

enable_testing()
add_test(testGridWorld tests/testGridWorld)
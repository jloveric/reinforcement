cmake_minimum_required(VERSION 3.18)
MESSAGE( STATUS "Boost paths:         " ${Boost_LIBRARIES} )
set(CMAKE_CXX_STANDARD 20)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/source)

set(THESE_LIBS 
 boost_filesystem
 boost_graph
 boost_program_options
 boost_regex
 boost_system
 #UnitTest++
)

add_executable(testGridWorld testGridWorld.cpp)
target_link_libraries(testGridWorld ${THESE_LIBS} ${Boost_LIBRARIES} )
# Should be able to handle cmake following this here
# https://gitlab.kitware.com/cmake/cmake/-/blob/master/Help/dev/experimental.rst
# but maybe wait a bit. 
# TODO: This does not work yet!

cmake_minimum_required(VERSION 3.18)

# set the project name
project(Reinforce)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PREBUILT_MODULE_PATH ${CMAKE_BINARY_DIR}/modules)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
string(CONCAT CMAKE_EXPERIMENTAL_CXX_SCANDEP_SOURCE
  "<CMAKE_CXX_COMPILER> <DEFINES> <INCLUDES> <FLAGS> <SOURCE>"
  " -MT <DYNDEP_FILE> -MD -MF <DEP_FILE>"
  " ${flags_to_scan_deps} -fdep-file=<DYNDEP_FILE> -fdep-output=<OBJECT>"
  )



# add the executable
add_executable(Reinforce main.cxx)
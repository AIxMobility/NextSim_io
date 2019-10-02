# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(gookto_io_2 DESCRIPTION "io parsing for the VN testing stage")


# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_MACOSX_RPATH 1)

add_library(app SHARED sources/gookto_io/intersection/connection.cpp sources/gookto_io/intersection/intersectionPhase.cpp sources/gookto_io/intersection/port.cpp sources/gookto_io/InputLink.cpp 
sources/gookto_io/InputAgents.cpp sources/gookto_io/IntersectionNode.cpp 
sources/gookto_io/LinkArr.cpp sources/gookto_io/NodeArr.cpp tinyapi/tinystr.cpp tinyapi/tinyxml.cpp tinyapi/tinyxmlerror.cpp 
tinyapi/tinyxmlparser.cpp sources/gookto_io/AgentsArr.cpp sources/gookto_io/ParamArr.cpp)

include_directories(includes)

add_subdirectory(sources/gookto_io)
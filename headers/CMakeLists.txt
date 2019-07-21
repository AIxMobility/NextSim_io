# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name

project(gookto_io)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(app main3.cpp ./intersection/connection.cpp ./intersection/intersectionPhase.cpp ./intersection/port.cpp InputLink.cpp InputVeh.cpp IntersectionNode.cpp 
LinkArr.cpp NodeArr.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp VehArr.cpp)
#add_executable(intersectionPhase ${PROJECT_SOURCE_DIR}/intersection/intersectionPhase.cpp)
#add_executable(port ${PROJECT_SOURCE_DIR}/intersection/port.cpp)

#add_executable(InputLink ${PROJECT_SOURCE_DIR}/InputLink.cpp)
#add_executable(InputVeh ${PROJECT_SOURCE_DIR}/InputVeh.cpp)
#add_executable(IntersectionNode ${PROJECT_SOURCE_DIR}/IntersectionNode.cpp)
#add_executable(LinkArr ${PROJECT_SOURCE_DIR}/LinkArr.cpp)
#add_executable(main ${PROJECT_SOURCE_DIR}/main3.cpp)
#add_executable(NodeArr ${PROJECT_SOURCE_DIR}/NodeArr.cpp)

#add_executable(tinystr ${PROJECT_SOURCE_DIR}/tinystr.cpp)
#add_executable(tinyxml ${PROJECT_SOURCE_DIR}/tinyxml.cpp)
#add_executable(tinyxmlerror ${PROJECT_SOURCE_DIR}/tinyxmlerror.cpp)
#add_executable(tinyxmlparser ${PROJECT_SOURCE_DIR}/tinyxmlparser.cpp)

#add_executable(VehArr ${PROJECT_SOURCE_DIR}/VehArr.cpp)
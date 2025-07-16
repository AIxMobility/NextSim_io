cmake_minimum_required(VERSION 3.14)
project(FootpathTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(target FootpathTest)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../includes    # InputStation 등
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../rapidjson/include
    /home/yeonwoo/NextSim/Captain/Libraries/NextSim_io/includes  # 헤더 포함 경로 (필요하면 추가)
)

# TinyXML 소스 파일들 (예: tinyapi 폴더 내 cpp 파일 모두 포함)
file(GLOB TINYXML_SOURCES
    /home/yeonwoo/NextSim/Captain/Libraries/NextSim_io/sources/NextSim_io/tinyapi/*.cpp
)

# 프로젝트 소스 파일
set(sources
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FootpathRouteGenerator.cpp
    /home/yeonwoo/NextSim/Captain/Libraries/NextSim_io/sources/NextSim_io/inputclass/InputStation.cpp
    ${TINYXML_SOURCES}   # TinyXML 소스 포함
)

add_executable(${target} ${sources})

# 필요한 라이브러리가 있으면 여기에 링크 (예: pthread, math 등)
# target_link_libraries(${target} ...)

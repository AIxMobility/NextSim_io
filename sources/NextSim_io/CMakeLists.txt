set(includes_dir ${InputXmlParser_SOURCE_DIR}/includes/NextSim_io)

file(GLOB_RECURSE headers
        ${includes_dir}/parser/*.hpp
        ${includes_dir}/inputclass/*.hpp
        ${includes_dir}/inputclass/intersection/*.hpp
        ${includes_dir}/tinyapi/*.h)

file(GLOB_RECURSE sources
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/inputclass/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tinyapi/*.cpp)


add_library(InputXmlParser ${headers} ${sources})

target_include_directories(InputXmlParser PUBLIC ../../includes)

target_compile_features(InputXmlParser PUBLIC cxx_std_11)


#have to add all source files to the executable
set(SOURCE_FILES ${InputXmlParser_SOURCE_DIR}/tests/main.cpp ${sources})

add_executable(Main ${SOURCE_FILES})

target_link_libraries(Main PRIVATE InputXmlParser)
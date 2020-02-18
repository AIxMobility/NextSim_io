add_executable(InputXmlParser main.cpp)

target_compile_features(TestParser PRIVATE cxx_std_17)


target_link_libraries(TestParser PRIVATE InputXmlParser)


add_test(NAME TestParserTest COMMAND TestParser)
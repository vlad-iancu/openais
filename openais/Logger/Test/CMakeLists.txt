add_executable(LoggerTest LoggerTest.cpp)
target_link_libraries(LoggerTest PUBLIC Logger gtest_main gmock)
set_target_properties(LoggerTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test)

include(GoogleTest)
gtest_discover_tests(LoggerTest)

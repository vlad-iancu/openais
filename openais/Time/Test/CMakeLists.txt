add_executable(TimeTest TimeTest.cpp)
target_link_libraries(TimeTest PUBLIC Time gtest_main gmock)
set_target_properties(TimeTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test)

include(GoogleTest)
gtest_discover_tests(TimeTest)
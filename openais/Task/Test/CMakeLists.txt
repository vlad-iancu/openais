#add_executable(TaskTest CommandLineTest.cpp TaskTest.cpp)
#target_link_libraries(TaskTest PUBLIC #[[TaskCommandLine]] Task gtest_main gmock)
#set_target_properties(TaskTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test)

#include(GoogleTest)
#gtest_discover_tests(TaskTest)
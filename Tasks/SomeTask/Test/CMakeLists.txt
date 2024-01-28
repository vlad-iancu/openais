add_executable(SomeTaskTest SomeTaskTest.cpp)
target_link_libraries(SomeTaskTest PUBLIC gtest_main)
set_target_properties(SomeTaskTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test)

include(GoogleTest)
gtest_discover_tests(SomeTaskTest)

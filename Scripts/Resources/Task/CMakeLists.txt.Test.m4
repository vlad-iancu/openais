define(TargetName, `taskName`TaskTest'')dnl
`add_executable'(TargetName TargetName.cpp)
`target_link_libraries'(TargetName PUBLIC gtest_main)
`set_target_properties'(TargetName PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Test)

`include(GoogleTest)'
`gtest_discover_tests'(TargetName)
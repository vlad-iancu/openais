define(TargetName, ``Output'interfaceName`Interface'')dnl
`add_library'`('TargetName STATIC TargetName.cpp`)'
`target_link_libraries'`('TargetName PUBLIC `${LOGGER_LIBS}'`)'
`target_include_directories'`('TargetName PUBLIC `${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/openais'`)'
`set_target_properties'`('TargetName PROPERTIES ARCHIVE_OUTPUT_DIRECTORY `${CMAKE_BINARY_DIR}/Lib'`)'

#!/bin/bash

interfaceType=$2
#Create CMakeLists.txt
TargetName=Input$1Interface

cat << EOF
add_library($TargetName STATIC $TargetName.cpp)
target_include_directories($TargetName PUBLIC \${CMAKE_CURRENT_SOURCE_DIR} \${CMAKE_SOURCE_DIR}/openais \${CMAKE_SOURCE_DIR}/Serialization)
set_target_properties($TargetName PROPERTIES ARCHIVE_OUTPUT_DIRECTORY \${CMAKE_BINARY_DIR}/Lib)
target_link_libraries($TargetName PRIVATE ${interfaceType})
EOF

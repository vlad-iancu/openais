#!/bin/bash

COMPONENT=$1
TASK=$2

if [ -z "$COMPONENT" ]; then
    echo "Component name is required"
    exit 1
fi

if [ -z "$TASK" ]; then
    echo "Task name is required"
    exit 1
fi

TARGET="${COMPONENT}Component"
cat << EOF
add_library($TARGET $TARGET.cpp)
target_link_libraries($TARGET PUBLIC \${Boost_LIBRARIES} Component)
target_include_directories($TARGET PUBLIC \${Boost_INCLUDE_DIRS} \${CMAKE_SOURCE_DIR}/openais)
EOF
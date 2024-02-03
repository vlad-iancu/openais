#!/bin/bash

cat << EOF
file(GLOB COMPONENTS "*")
foreach(COMPONENT \${COMPONENTS})
    if(IS_DIRECTORY \${COMPONENT})
        get_filename_component(COMPONENT_LIB \${COMPONENT} NAME)
        list(APPEND COMPONENT_LIBS "\${COMPONENT_LIB}Component")
        add_subdirectory(\${COMPONENT})
    endif()
endforeach()
set(COMPONENT_LIBS \${COMPONENT_LIBS} PARENT_SCOPE)
EOF
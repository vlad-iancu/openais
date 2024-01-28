#!/bin/bash

#define(`SampleTask', `taskName`Task'')dnl
#define(`ConfigFile', `"${CMAKE_BINARY_DIR}/Config/'taskName`TaskConfig.py"')dnl
#define(SAMPLE_TASK_CONFIG_FILENAME, `translit(taskName, `a-z', `A-Z')`_TASK_CONFIG_FILENAME'')dnl

SampleTask=$1Task
ConfigFile=\${CMAKE_BINARY_DIR}/Config/$1TaskConfig.py
SAMPLE_TASK_CONFIG_FILENAME=`echo $1 | tr 'a-z' 'A-Z'`_TASK_CONFIG_FILENAME


cat << EOF
include_directories("/usr/local/include/iceoryx/v2.90.0")
link_directories("/usr/local/lib") 
link_libraries(iceoryx_posh iceoryx_hoofs iceoryx_platform iceoryx_binding_c iceoryx_posh_config iceoryx_posh_gateway iceoryx_posh_roudi) 
add_executable ( $SampleTask $SampleTask.cpp )
set(INTERFACES InterfaceBase) 
target_link_libraries ( $SampleTask PUBLIC   \${OPENAIS_TASK}  -Wl,--whole-archive   \${INTERFACES}    \${LOGGER_LIBS}  -Wl,--no-whole-archive)
target_include_directories ($SampleTask PUBLIC   \${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_definitions ($SampleTask PUBLIC $SAMPLE_TASK_CONFIG_FILENAME=$ConfigFile)
set_target_properties ($SampleTask PROPERTIES RUNTIME_OUTPUT_DIRECTORY "\${CMAKE_BINARY_DIR}/Bin/" )
configure_file (  \${CMAKE_CURRENT_SOURCE_DIR}/config.py  $ConfigFile COPYONLY)
if(ENABLE_TESTING) 
add_subdirectory(Test) 
endif() 

EOF

define(`SampleTask', `taskName`Task'')dnl
define(`ConfigFile', `"${CMAKE_BINARY_DIR}/Config/'taskName`TaskConfig.py"')dnl
define(SAMPLE_TASK_CONFIG_FILENAME, `translit(taskName, `a-z', `A-Z')`_TASK_CONFIG_FILENAME'')dnl
`add_executable'(SampleTask taskName`Task.cpp')
`set(INTERFACES InterfaceBase)'
`target_link_libraries'(SampleTask PUBLIC `${OPENAIS_TASK}' -Wl,--whole-archive `${INTERFACES}' `${LOGGER_LIBS}' -Wl,--no-whole-archive)
`target_include_directories'(SampleTask PUBLIC `${CMAKE_CURRENT_SOURCE_DIR}')
`target_compile_definitions'(SampleTask PUBLIC SAMPLE_TASK_CONFIG_FILENAME=ConfigFile)
`set_target_properties'(SampleTask PROPERTIES RUNTIME_OUTPUT_DIRECTORY `"${CMAKE_BINARY_DIR}/Bin/"')

`configure_file'(`${CMAKE_CURRENT_SOURCE_DIR}/config.py' ConfigFile COPYONLY)
`if(ENABLE_TESTING)'
`add_subdirectory(Test)'
`endif()'

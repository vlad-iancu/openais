define(SampleTask, taskName`Task')dnl
define(ConfigFile, `"${CMAKE_BINARY_DIR}/Config/'taskName`TaskConfig.json"')dnl
define(SAMPLE_TASK_CONFIG_FILENAME, translit(taskName, `a-z', `A-Z')`_TASK_CONFIG_FILENAME')
`add_executable'(SampleTask taskName`Task.cpp')

`target_link_libraries'(SampleTask PUBLIC Task)
`target_include_directories'(SampleTask PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
`target_compile_definitions'(SampleTask PUBLIC SAMPLE_TASK_CONFIG_FILENAME=ConfigFile)
`set_target_properties'(SampleTask PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/")

add_custom_command(
        TARGET SampleTask POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/config.json
                ConfigFile
)

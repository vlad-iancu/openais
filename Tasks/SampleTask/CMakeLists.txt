add_executable(SampleTask SampleTask.cpp)

set(INTERFACES OutputSampleInterface InterfaceBase)

target_link_libraries(SampleTask PUBLIC Task -Wl,--whole-archive ${INTERFACES} -Wl,--no-whole-archive)
target_include_directories(SampleTask PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/openais)
target_compile_definitions(SampleTask PUBLIC SAMPLE_TASK_CONFIG_FILENAME="${CMAKE_BINARY_DIR}/Config/SampleTaskConfig.json")
set_target_properties(SampleTask PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin/")

add_custom_command(
        TARGET SampleTask POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/config.json
                ${CMAKE_BINARY_DIR}/Config/SampleTaskConfig.json)

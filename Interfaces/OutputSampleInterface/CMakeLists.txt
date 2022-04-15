add_library(OutputSampleInterface STATIC OutputSampleInterface.cpp)
target_include_directories(OutputSampleInterface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/openais)
set_target_properties(OutputSampleInterface PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

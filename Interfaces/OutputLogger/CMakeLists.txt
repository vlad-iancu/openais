add_library(OutputLoggerInterface STATIC OutputLoggerInterface.cpp)
target_include_directories(OutputLoggerInterface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/openais)
set_target_properties(OutputLoggerInterface PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

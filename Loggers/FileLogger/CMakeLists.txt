
add_library(FileLogger FileLogger.cpp)
target_include_directories(FileLogger PUBLIC ${CMAKE_SOURCE_DIR}/openais ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(FileLogger PUBLIC Task Logger)
set_target_properties(FileLogger PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

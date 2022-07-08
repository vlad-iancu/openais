add_library(ConsoleLogger ConsoleLogger.cpp)
target_include_directories(ConsoleLogger PUBLIC ${CMAKE_SOURCE_DIR}/openais ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ConsoleLogger PUBLIC Logger)
set_target_properties(ConsoleLogger PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

include("${CMAKE_SOURCE_DIR}/openais/Python.cmake")
add_library(Logger Logger.cpp LogEntry.cpp Log.cpp)
target_link_libraries(Logger PUBLIC Time ${PYTHON_LIBRARIES})

target_include_directories(Logger PUBLIC ${CMAKE_SOURCE_DIR}/openais ${PYTHON_INCLUDE_DIRS})
set_target_properties(Logger PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)



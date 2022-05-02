add_library(Time Time.cpp)
target_link_libraries(Time PUBLIC pthread)
target_include_directories(Time PUBLIC ${CMAKE_SOURCE_DIR}/openais)
set_target_properties(Time PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

if(ENABLE_TESTING)
add_subdirectory(Test)
endif()


add_library(InterfaceBase STATIC
            Interface.cpp
            InterfaceDB.cpp)

target_include_directories(InterfaceBase PUBLIC ${CMAKE_SOURCE_DIR}/openais)
set_target_properties(InterfaceBase PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

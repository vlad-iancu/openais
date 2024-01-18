add_library(Person Person.pb.cc)
target_link_libraries(Person PRIVATE protobuf pthread)
target_include_directories(Person PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
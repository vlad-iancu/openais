add_library(Person SHARED Person.pb.cc)
target_link_libraries(Person protobuf pthread)
target_include_directories(Person PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
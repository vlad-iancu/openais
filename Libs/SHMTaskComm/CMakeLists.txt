include_directories("/usr/local/include/iceoryx/v2.90.0")
link_directories("/usr/local/lib")
link_libraries(iceoryx_posh iceoryx_hoofs iceoryx_platform iceoryx_binding_c iceoryx_posh_config iceoryx_posh_gateway iceoryx_posh_roudi)
# add_library(SHMTaskComm SHMBlock.cpp SHMTaskCommClient.cpp)
# target_link_libraries(SHMTaskComm PUBLIC ${Boost_LIBRARIES} SHMTypes)
# target_include_directories(SHMTaskComm PUBLIC ${CMAKE_SOURCE_DIR}/Libs)
# set_target_properties(SHMTaskComm PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

add_executable(SHMTaskCommPublisher SHMTaskCommPublisher.cpp)
#target_link_libraries(SHMTaskCommPublisher PUBLIC SHMTaskComm SHMTypes)
target_include_directories(SHMTaskCommPublisher PUBLIC ${CMAKE_SOURCE_DIR}/Libs)
set_target_properties(SHMTaskCommPublisher PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

#Add executable SHMTaskCommSubscriber
add_executable(SHMTaskCommSubscriber SHMTaskCommSubscriber.cpp)
#target_link_libraries(SHMTaskCommSubscriber PUBLIC SHMTaskComm SHMTypes)
target_include_directories(SHMTaskCommSubscriber PUBLIC ${CMAKE_SOURCE_DIR}/Libs)
set_target_properties(SHMTaskCommSubscriber PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
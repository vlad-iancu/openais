set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/BuildDependencies/boost)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

find_package(Boost REQUIRED COMPONENTS filesystem program_options)

add_library(Task STATIC Task.cpp PeriodicTask.cpp ContinualTask.cpp)
add_library(TaskMain STATIC TaskMain.cpp)
add_library(TaskConfig STATIC Config.cpp)
add_library(TaskCommandLine STATIC CommandLine.cpp)
add_library(Main STATIC Main.cpp)

target_link_libraries(TaskMain PUBLIC TaskCommandLine TaskConfig Task pthread)
target_link_libraries(TaskConfig PUBLIC Boost::filesystem)
target_link_libraries(TaskCommandLine PUBLIC Boost::filesystem Boost::program_options)
target_link_libraries(Main PUBLIC TaskMain)

target_include_directories(Task PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskMain PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskConfig PUBLIC ${CMAKE_SOURCE_DIR}/openais)
target_include_directories(TaskCommandLine PUBLIC ${CMAKE_SOURCE_DIR}/openais)

set_target_properties(Task PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskMain PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskConfig PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskCommandLine PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

if(ENABLE_TESTING)
add_subdirectory(Test)
endif()


set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/BuildDependencies/boost)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

find_package(Boost REQUIRED COMPONENTS filesystem program_options)

add_library(Task STATIC Task.cpp TaskMain.cpp Config.cpp CommandLine.cpp)
target_link_libraries(Task PUBLIC InterfaceBase Boost::filesystem Boost::program_options pthread)
target_include_directories(Task PUBLIC ${CMAKE_SOURCE_DIR}/openais)

set_target_properties(Task PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)


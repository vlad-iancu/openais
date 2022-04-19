set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/BuildDependencies/boost)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)

find_package(Boost REQUIRED)

add_library(InputNumberStringProviderInterface STATIC InputNumberStringProviderInterface.cpp)
target_link_libraries(InputNumberStringProviderInterface PUBLIC pthread)
target_include_directories(InputNumberStringProviderInterface PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/openais 
    ${Boost_INCLUDE_DIRS})
set_target_properties(InputNumberStringProviderInterface PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
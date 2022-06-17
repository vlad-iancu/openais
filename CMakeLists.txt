cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

option(ENABLE_TESTING "Enables Testing" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

if(ENABLE_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/BuildDependencies/googletest
    )
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_custom_target(tests ${CMAKE_CTEST_COMMAND})
endif()

set(DOXYGEN ${CMAKE_SOURCE_DIR}/BuildDependencies/doxygen/build/target/bin/doxygen)
set(DOXYGEN_PROPERTIES "")

add_custom_target(docs
    COMMAND cat ${CMAKE_SOURCE_DIR}/Doxyfile ${CMAKE_SOURCE_DIR}/Doxyfile.in | ${DOXYGEN} -
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_subdirectory(openais)
add_subdirectory(Interfaces)
add_subdirectory(Tasks)
include("Config/Config.cmake")


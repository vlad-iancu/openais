cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)
option(ENABLE_TESTING "Enables Testing" ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)

if ( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message(STATUS "We are debugging")
    add_compile_definitions(OPENAIS_DEBUG="VAL")
    set(OPENAIS_DEBUG "TRUE")
else()
    unset(OPENAIS_DEBUG)
endif()

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

#set(DOXYGEN ${CMAKE_SOURCE_DIR}/BuildDependencies/doxygen/build/target/bin/doxygen)
#set(DOXYGEN_PROPERTIES "")

find_package(Doxygen REQUIRED)

add_custom_target(docs
    COMMAND cat ${CMAKE_SOURCE_DIR}/Doxyfile ${CMAKE_SOURCE_DIR}/Doxyfile.in | ${DOXYGEN} -
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_subdirectory(Libs)
add_subdirectory(openais)
add_subdirectory(Loggers)
add_subdirectory(Interfaces)
add_subdirectory(Tasks)
add_subdirectory(Serialization)
#Multiple definition in ld is because of -Wl,--whole-archive, find a way around that
include("Config/Config.cmake")

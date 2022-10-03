find_package(Boost REQUIRED COMPONENTS serialization)
set(SOURCES
    Src/TMPMessages/TMPPauseMessage.cpp
    Src/TMPMessages/TMPRequestNameMessage.cpp
    Src/TMPMessages/TMPRequestStatusMessage.cpp
    Src/TMPMessages/TMPResponseNameMessage.cpp
    Src/TMPMessages/TMPResponseStatusMessage.cpp
    Src/TMPMessages/TMPResumeMessage.cpp
    Src/TMPMessages/TMPStopMessage.cpp
    Src/TMPConnection.cpp
    Src/TMPMessage.cpp
    )

add_library(TMP STATIC ${SOURCES})
target_include_directories(TMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Src)
set_target_properties(TMP PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
target_link_libraries(TMP PUBLIC Boost::serialization)

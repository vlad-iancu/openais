find_package(Boost REQUIRED COMPONENTS filesystem program_options)

include("${CMAKE_SOURCE_DIR}/openais/Python.cmake")

add_library(Task STATIC 
        Task.cpp 
        PeriodicTask.cpp 
        ContinualTask.cpp 

)
if(OPENAIS_DEBUG)
add_library(TaskManagerClient TaskManager/TaskManagerClient/TMPClient.cpp)
endif()
add_library(TaskMain STATIC TaskMain.cpp)
add_library(TaskConfig STATIC Config.cpp Interpreter.cpp)
add_library(Main STATIC Main.cpp)

if(OPENAIS_DEBUG)
add_executable(TaskManagerServer 
        TaskManager/TaskManagerServer/TMPServer.cpp
        TaskManager/TaskManagerServer/Main.cpp
)
endif()

target_link_libraries(TaskMain PUBLIC Logger Task pthread stdc++fs)
target_link_libraries(TaskConfig PUBLIC Boost::filesystem ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})
if(DEFINED OPENAIS_DEBUG)
target_link_libraries(TaskManagerClient TMP)
endif()

set(TASK_LINK_LIBS "TaskConfig")
if(OPENAIS_DEBUG)
        list(APPEND TASK_LINK_LIBS "TaskManagerClient")
endif()

target_link_libraries(Task PUBLIC ${TASK_LINK_LIBS})
target_link_libraries(Main PUBLIC TaskMain)

if(DEFINED OPENAIS_DEBUG)
target_link_libraries(TaskManagerServer PUBLIC TaskConfig TMP)
endif()

target_include_directories(Task PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskMain PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskConfig PUBLIC ${CMAKE_SOURCE_DIR}/openais ${PYTHON_INCLUDE_DIRS})
if(DEFINED OPENAIS_DEBUG)
target_include_directories(TaskManagerClient PUBLIC ${CMAKE_SOURCE_DIR}/openais ${PYTHON_INCLUDE_DIRS})
endif()

if(DEFINED OPENAIS_DEBUG)
target_include_directories(TaskManagerServer PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
endif()

target_compile_options(TaskConfig PUBLIC ${PYTHON_CFLAGS_OTHER})
if(OPENAIS_DEBUG)
target_compile_options(TaskManagerServer PUBLIC ${PYTHON_CFLAGS_OTHER})
endif()

set_target_properties(Task PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskMain PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskConfig PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
if(DEFINED OPENAIS_DEBUG)
set_target_properties(TaskManagerClient PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
endif()
if(OPENAIS_DEBUG)
set_target_properties(TaskManagerServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)
endif()

if(ENABLE_TESTING)
add_subdirectory(Test)
endif()


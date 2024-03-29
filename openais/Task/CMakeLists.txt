find_package(Boost REQUIRED COMPONENTS filesystem program_options)

include("${CMAKE_SOURCE_DIR}/openais/Python.cmake")

add_library(Task STATIC 
        Task.cpp 
        PeriodicTask.cpp 
        ContinualTask.cpp 

)

add_library(TaskMain STATIC TaskMain.cpp)
add_library(TaskConfig STATIC Config.cpp Interpreter.cpp)
add_library(Component STATIC Component.cpp)
add_library(Main STATIC Main.cpp)



target_link_libraries(TaskMain PUBLIC Logger Task pthread Component stdc++fs)
target_link_libraries(TaskConfig PUBLIC Boost::filesystem ${PYTHON_LIBRARIES} ${Boost_LIBRARIES})


set(TASK_LINK_LIBS "TaskConfig")

target_link_libraries(Task PUBLIC ${TASK_LINK_LIBS} Component)
target_link_libraries(Main PUBLIC TaskMain)
target_link_libraries(Component PUBLIC TaskConfig)


target_include_directories(Task PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskMain PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})
target_include_directories(TaskConfig PUBLIC ${CMAKE_SOURCE_DIR}/openais ${PYTHON_INCLUDE_DIRS})
target_include_directories(Component PUBLIC ${CMAKE_SOURCE_DIR}/openais ${Boost_INCLUDE_DIRS})

target_compile_options(TaskConfig PUBLIC ${PYTHON_CFLAGS_OTHER})

set_target_properties(Task PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskMain PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(TaskConfig PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(Component PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)
set_target_properties(Main PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Lib)

if(ENABLE_TESTING)
add_subdirectory(Test)
endif()


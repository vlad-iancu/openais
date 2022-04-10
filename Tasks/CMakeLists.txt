file(GLOB TASKS "*")
foreach(TASK ${TASKS})
    if(IS_DIRECTORY ${TASK}) # This was changed
        add_subdirectory(${TASK})
    endif()
endforeach()

file(GLOB LIBS "*")
foreach(LIB ${LIBS})
    if(IS_DIRECTORY ${LIB})
        add_subdirectory(${LIB})
    endif()
endforeach()

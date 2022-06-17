file(GLOB CONFIG_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/Config/*.py")

foreach(CONFIG_FILE ${CONFIG_FILES})
    #message(STATUS "Config file \"${CONFIG_FILE}\"")
    get_filename_component(CONFIG_FILE_NAME ${CONFIG_FILE} NAME)
    configure_file(${CONFIG_FILE} "${CMAKE_BINARY_DIR}/Config/${CONFIG_FILE_NAME}")
endforeach(CONFIG_FILE ${CONFIG_FILES})

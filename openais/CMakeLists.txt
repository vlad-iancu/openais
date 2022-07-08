add_subdirectory(Task)
add_subdirectory(Interface)
add_subdirectory(Time)
add_subdirectory(Logger)

set(OPENAIS_TASK Logger Task TaskMain Main TaskConfig Time PARENT_SCOPE)

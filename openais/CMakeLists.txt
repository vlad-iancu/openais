add_subdirectory(Task)
add_subdirectory(Interface)
add_subdirectory(Time)
add_subdirectory(Logger)

set(OPENAIS_TASK Task TaskMain Main TaskConfig #[[TaskCommandLine]] Time PARENT_SCOPE)

add_subdirectory(Task)
add_subdirectory(Interface)
add_subdirectory(Time)

set(OPENAIS_TASK Task TaskMain Main TaskConfig #[[TaskCommandLine]] Time PARENT_SCOPE)
set(OPENAIS "Task InterfaceBase")

add_subdirectory(Task)
add_subdirectory(Interface)

set(OPENAIS_TASK Task TaskMain Main TaskConfig TaskCommandLine PARENT_SCOPE)
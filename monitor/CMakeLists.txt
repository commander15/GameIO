cm_add_executable(monitor main.cpp gamepadlogger.cpp)

target_link_libraries(monitor PRIVATE gameio)

cm_add_executable(monitor main.cpp res.qrc
    gamepadwidget.cpp
    gamepadlogger.cpp
)

target_link_libraries(monitor PRIVATE Qt::Widgets gameio)

qt_add_executable(Monitor main.cpp res.qrc
    gamepadwidget.cpp gamepadwidget.ui
    gamepadlogger.cpp
)

target_link_libraries(Monitor PRIVATE Qt::Widgets GameIO)

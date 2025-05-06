qt_add_executable(ball main.cpp)

qt_add_qml_module(ball
    URI Ball
    VERSION 1.0
    QML_FILES App.qml
    RESOURCES resources.qrc
    QML_FILES Ball.qml
)

target_link_libraries(ball PRIVATE Qt::Quick GameIO)

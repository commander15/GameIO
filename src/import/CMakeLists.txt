qt_add_qml_module(GameIOQml
    URI GameIO
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    CLASS_NAME GameIOQmlPlugin
    TYPEINFO GameIO.qmltypes
    PLUGIN_TARGET GameIOQml
    SOURCES gamepadmanager.h gamepadmanager.cpp
    SOURCES gamepad.h gamepad.cpp
)

target_link_libraries(GameIOQml PUBLIC Qt::Qml Qt::Gui GameIO)

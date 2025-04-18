qt_add_qml_module(GameIOQml
    URI GameIO
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    TYPEINFO GameIO
    PLUGIN_TARGET GameIOQml
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES plugin.cpp
)

target_link_libraries(GameIOQml PUBLIC GameIO)

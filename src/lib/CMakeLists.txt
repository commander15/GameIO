qt_add_library(GameIO)

set_target_properties(GameIO PROPERTIES
    OUTPUT_NAME GameIO
    VERSION     ${PROJECT_VERSION}
)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

target_headers(GameIO
    PUBLIC
        gameio.h
        global.h config.h
        gamepadmanager.h gamepad.h
    PRIVATE
        debug_p.h
        gamepadmanager_p.h gamepad_p.h
)

target_sources(GameIO
    PRIVATE
        debug.cpp
        gamepadmanager.cpp
        gamepad.cpp
        gameio_res.qrc
)

target_include_directories(GameIO 
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<INSTALL_INTERFACE:include/GameIO>
)

target_compile_definitions(GameIO
    PUBLIC
        $<IF:$<STREQUAL:$<TARGET_PROPERTY:TYPE>,STATIC_LIBRARY>,GAMEIO_STATIC,GAMEIO_SHARED>
    INTERFACE
        GAMEIO_LIB
    PRIVATE
        GAMEIO_BUILD
)

target_link_libraries(GameIO PUBLIC Qt::Core Qt::Gui SDL2::SDL2)

install(TARGETS GameIO
    EXPORT GameIOTargets
    ARCHIVE        DESTINATION lib
    LIBRARY        DESTINATION lib
    RUNTIME        DESTINATION bin
    PUBLIC_HEADER  DESTINATION include/GameIO
    #PRIVATE_HEADER DESTINATION include/GameIO/private
)

generate_target_headers(GameIO FOLDER GameIO)

cm_add_library(gameio)

target_link_libraries(gameio PUBLIC Qt::Core Qt::Gui SDL2::SDL2)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)

target_headers(gameio
    PUBLIC
        global.h config.h
        gamepadmanager.h gamepad.h
    PRIVATE
        gamepadmanager_p.h gamepad_p.h
)

target_sources(gameio
    PRIVATE
        gamepadmanager.cpp gamepad.cpp
)

target_include_directories(gameio
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

generate_target_headers(gameio FOLDER GameIO)

cm_install(TARGETS gameio
    EXPORT  GameIOTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/GameIO
)

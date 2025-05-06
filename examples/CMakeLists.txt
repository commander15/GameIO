if (GAMEIO_BUILD_QML)
    add_compile_definitions(
        QML_IMPORT_PATH="${QT_QML_OUTPUT_DIRECTORY}"
    )

    add_subdirectory(ball)
endif()

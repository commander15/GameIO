cmake_minimum_required(VERSION 3.30)

project(GameIO
    DESCRIPTION "Gaming I/O Qt library"
    VERSION     "2.0.0"
    LANGUAGES   CXX C
)

# Project settings

option(GAMEIO_BUILD_MONITOR      OFF "Build GameIO monitor tool")
option(GAMEIO_BUILD_QML          ON  "Build GameIO QML module")
option(GAMEIO_BUILD_TESTS        OFF "Build GameIO tests")
option(GAMEIO_BUILD_DOCS         OFF "Build GameIO documentation")
option(GAMEIO_BUILD_TRANSLATIONS OFF "Build GameIO translations")
option(GAMEIO_BUILD_EXAMPLES     OFF "Build GameIO examples")

set(GAMEIO_LOCALES en fr)

# CMake options
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# CXX Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# C Standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Registering project module path
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Including utility scripts
include(cmake/Utils.cmake)

# Qt setup

set(QT_QML_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY} CACHE STRING "")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(Qt_MODULES Core)

if (GAMEIO_BUILD_MONITOR)
    list(APPEND Qt_MODULES Widgets)
endif()

if (GAMEIO_BUILD_QML)
    list(APPEND Qt_MODULES Qml Gui)
endif()

if (GAMEIO_BUILD_TESTS)
    list(APPEND Qt_MODULES Test)
endif()

if (GAMEIO_BUILD_EXAMPLES)
    list(APPEND Qt_MODULES Quick)
endif()

if (GAMEIO_BUILD_TRANSLATIONS)
    list(APPEND Qt_MODULES LinguistTools)
endif()

find_package(Qt6 REQUIRED COMPONENTS ${Qt_MODULES})

qt_standard_project_setup(
    REQUIRES 6.8.0
    I18N_SOURCE_LANGUAGE      en
    I18N_TRANSLATED_LANGUAGES ${GAMEIO_LOCALES}
)

if (Qt6Qml_FOUND)
    qt_policy(SET QTP0001 NEW)
endif()

qt_policy(SET QTP0002 NEW)
qt_policy(SET QTP0003 NEW)

# Other dependencies
find_package(SDL2 REQUIRED)

# Project directories

add_subdirectory(src)

if (GAMEIO_BUILD_MONITOR)
    add_subdirectory(monitor)
endif()

if (GAMEIO_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (GAMEIO_BUILD_DOCS)
    add_subdirectory(docs)
endif()

if (GAMEIO_BUILD_TRANSLATIONS)
    qt_collect_translation_source_targets(SOURCE_TARGETS)

    qt_add_translations(GameIO SOURCE_TARGETS ${SOURCE_TARGETS}
        TS_FILE_BASE gameio
        TS_FILE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/translations
        QM_FILES_OUTPUT_VARIABLE QM_FILES
    )
    
    # Ensure the build directory has a translations folder
    set(TRANSLATIONS_BUILD_DIR "${CMAKE_BINARY_DIR}/translations")
    file(MAKE_DIRECTORY ${TRANSLATIONS_BUILD_DIR})

    # Copy QM files to build directory after they are generated
    add_custom_command(
        TARGET GameIO_lrelease POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${QM_FILES} ${TRANSLATIONS_BUILD_DIR}
        COMMENT "Copying generated QM files to ${TRANSLATIONS_BUILD_DIR}"
    )

    install(FILES ${QM_FILES} DESTINATION translations)
endif()

if (GAMEIO_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

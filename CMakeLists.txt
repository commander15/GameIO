cmake_minimum_required(VERSION 3.20)

project(GameIO
    DESCRIPTION "Gaming Input Output Library"
    VERSION     1.0.0
    LANGUAGES   CXX C
)

option(GAMEIO_BUILD_TEST    "Build tests" OFF)
option(GAMEIO_BUILD_MONITOR "Build gamepad monitor tool")

set(CMAKE_AUTOMOC ON)

find_package(Cm REQUIRED)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

find_package(SDL2 REQUIRED)

cm_add_package(GameIO
    NAME    GameIO
    VERSION ${GameIO_VERSION}
    EXPORTS GameIOTargets
)

add_subdirectory(src)

if (GAMEIO_BUILD_TEST)
    add_subdirectory(test)
endif()

if (GAMEIO_BUILD_MONITOR)
    add_subdirectory(monitor)
endif()

cm_install(PACKAGES GameIO
    DESTINATION lib/cmake
)

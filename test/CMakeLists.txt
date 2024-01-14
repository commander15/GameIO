find_package(GTest REQUIRED)

cm_add_executable(gameio_test
    main.cpp
    gamepadtest.cpp
)

target_link_libraries(gameio_test PRIVATE GTest::gtest gameio)

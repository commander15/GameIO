cm_add_executable(gameio_test
    main.cpp
    gamepadtest.cpp
)

target_link_libraries(gameio_test PRIVATE gameio)

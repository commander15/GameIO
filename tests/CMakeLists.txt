enable_testing()

find_package(GTest REQUIRED)

add_executable(GameIOTest
    main.cpp
)

target_compile_definitions(GameIOTest PRIVATE TEST_DATA_DIR="${PROJECT_SOURCE_DIR}/testdata")

target_link_libraries(GameIOTest PRIVATE GTest::gtest Qt::Test GameIO)

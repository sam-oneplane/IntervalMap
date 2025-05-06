find_package(GTest REQUIRED)

add_executable(interval_map_tests IntervalMap_test.cpp)

target_link_libraries(interval_map_tests
    mylib
    GTest::GTest
    GTest::Main
    pthread
)

add_test(NAME IntervalMapTest COMMAND interval_map_tests)

include(GoogleTest)
gtest_discover_tests(interval_map_tests)

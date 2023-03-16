project(tests)

add_executable(Google_Tests_run
        node_test.cpp
        list_test.cpp
        )

target_link_libraries(Google_Tests_run mywhs)

target_link_libraries(Google_Tests_run gtest gtest_main)

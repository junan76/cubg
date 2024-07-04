enable_testing()

add_executable(test-template test-template.cpp)
target_link_libraries(test-template gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(test-template)
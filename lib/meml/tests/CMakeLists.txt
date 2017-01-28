project(meml_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(TEST_FILES SanityCheck.cpp)
add_executable(meml_test ${TEST_FILES})
target_link_libraries(meml_test gtest gtest_main)
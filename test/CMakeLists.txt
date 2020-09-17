cmake_minimum_required(VERSION 3.17)
project(Eyeglass_test)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES testfile.cpp UtilityFixture.cpp ModelFixture.cpp)
add_executable(Eyeglass_test ${TEST_SOURCE_FILES})

set(DEPENDENCIES ${wxWidgets_LIBRARIES})

target_link_libraries(Eyeglass_test gtest gtest_main core ${DEPENDENCIES})

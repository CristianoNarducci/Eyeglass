cmake_minimum_required(VERSION 3.16)
project(Eyeglass_tests)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES testfile.cpp UtilityFixture.cpp)
add_executable(Eyeglass_tests ${TEST_SOURCE_FILES})

set(DEPENDENCIES ${wxWidgets_LIBRARIES})

target_link_libraries(Eyeglass_tests gtest gtest_main core ${DEPENDENCIES})

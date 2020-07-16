cmake_minimum_required(VERSION 3.16)
project(Eyeglass)

set(CMAKE_CXX_STANDARD 11)

# Tells cmake where to search for wxwidget (reports missing if not specified)
find_program(wxWidgets_CONFIG_EXECUTABLE "wx-config-gtk3")

# Find and add wxWidget to the project
find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})

# Adds test suite files
add_subdirectory(test)

add_executable(Eyeglass src/main.cpp)

set(PROJECT_SOURCE_FILES
	src/main.cpp
)
set(DEPENDENCIES
	${wxWidgets_LIBRARIES}
)

add_library(core ${PROJECT_SOURCE_FILES})
target_link_libraries(Eyeglass core ${DEPENDENCIES})


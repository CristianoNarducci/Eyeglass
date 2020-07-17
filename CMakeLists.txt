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
		src/view/AbstractView.h src/view/View.cpp src/view/View.h src/utils/Observer.h src/view/ViewTab.h src/view/OriginalViewTab.cpp src/view/OriginalViewTab.h src/view/DiffListTab.cpp src/view/DiffListTab.h src/view/SideBySideTab.cpp src/view/SideBySideTab.h src/view/LayerTab.cpp src/view/LayerTab.h src/view/HeatmapTab.cpp src/view/HeatmapTab.h src/controllers/AbstractController.h src/controllers/controller.cpp src/controllers/controller.h)
set(DEPENDENCIES ${wxWidgets_LIBRARIES})

add_library(core ${PROJECT_SOURCE_FILES})
target_link_libraries(Eyeglass core ${DEPENDENCIES})


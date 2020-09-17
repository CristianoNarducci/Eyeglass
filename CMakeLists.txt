cmake_minimum_required(VERSION 3.17)
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
		src/model/Model.h
		src/model/Model.cpp
		src/model/PixelDiff.h
		src/utils/ImageUtils.h
		src/utils/Subject.h
		src/utils/Observer.h
		src/exception/ImageLoaderException.h
		src/exception/ImageGeometryException.h
		src/controller/Controller.h
		src/controller/Controller.cpp
		src/view/View.h
		src/view/View.cpp
		src/view/ViewTab.h
		src/view/ViewTab.cpp
		src/view/OriginalViewTab.h
		src/view/OriginalViewTab.cpp
		src/view/SideBySideTab.h
		src/view/SideBySideTab.cpp
		src/view/LayerTab.h
		src/view/LayerTab.cpp
		src/view/HeatmapTab.h
		src/view/HeatmapTab.cpp
		src/view/DiffListTab.h
		src/view/DiffListTab.cpp)
set(DEPENDENCIES ${wxWidgets_LIBRARIES})

add_library(core ${PROJECT_SOURCE_FILES})
target_link_libraries(Eyeglass core ${DEPENDENCIES})


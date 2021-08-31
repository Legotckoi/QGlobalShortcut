cmake_minimum_required(VERSION 3.12)
project(qglobalshortcut VERSION 1.0.0 LANGUAGES CXX)

option(QGLOBALSHORTCUT_BUILD_TESTS "Build test tree" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

message(STATUS "Qt Version: ${QT_VERSION}")
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
	find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets)
	find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
	add_library(qglobalshortcut STATIC qglobalshortcut.h win/qglobalshortcut.cpp)
	target_link_libraries(qglobalshortcut PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
	if(MSVC)
		target_link_libraries(qglobalshortcut PRIVATE user32)
	endif()

elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
	find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets X11Extras)
	find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets X11Extras)
	add_library(qglobalshortcut STATIC qglobalshortcut.h x11/qglobalshortcut.cpp)
	target_link_libraries(qglobalshortcut PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
	target_link_libraries(qglobalshortcut PRIVATE Qt${QT_VERSION_MAJOR}::X11Extras)
	target_link_libraries(qglobalshortcut PRIVATE X11)

else()
	message(FATAL_ERROR "Not supported platform: ${CMAKE_SYSTEM_NAME}.")
endif()

if(QGLOBALSHORTCUT_BUILD_TESTS)
	add_subdirectory(tests)
endif()

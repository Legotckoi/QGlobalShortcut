cmake_minimum_required(VERSION 3.12)
project(qglobalshortcut_tests VERSION 0.1.0 LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(TESTS_SOURCES
	main.cpp
	mainwindow.cpp
	mainwindow.h
	mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(qglobalshortcut_tests WIN32 MANUAL_FINALIZATION ${TESTS_SOURCES})
else()
	if(ANDROID)
		add_library(qglobalshortcut_tests SHARED ${TESTS_SOURCES})
	else()
		add_executable(qglobalshortcut_tests WIN32 ${TESTS_SOURCES})
	endif()
endif()

add_dependencies(qglobalshortcut_tests qglobalshortcut)

target_include_directories(qglobalshortcut_tests PRIVATE ../)
target_link_libraries(qglobalshortcut_tests PRIVATE qglobalshortcut)
target_link_libraries(qglobalshortcut_tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(qglobalshortcut_tests)
endif()

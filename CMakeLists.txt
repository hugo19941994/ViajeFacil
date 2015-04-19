cmake_minimum_required(VERSION 3.1)
project(ViajeFacil_master)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

# The Qt5Widgets_INCLUDES also includes the include directories for
# dependencies QtCore and QtGui
include_directories(${Qt5Widgets_INCLUDES})

# We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
add_definitions(${Qt5Widgets_DEFINITIONS})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS} -std=c++11")

set(SOURCE_FILES
    fecha.cpp
    fecha.h
    header.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    nego.h
    negos.cpp
    oficinas.cpp
    oficinas.h
    owner.h
    peticion.h
    peticiones.cpp
    ui_mainwindow.h)

add_executable(ViajeFacil_master ${SOURCE_FILES})

target_link_libraries(ViajeFacil_master ${Qt5Widgets_LIBRARIES})

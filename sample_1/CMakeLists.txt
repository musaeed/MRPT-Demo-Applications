cmake_minimum_required(VERSION 2.8.11)

project(qt_mrpt)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11)
# Find the QtWidgets library

#Set the mrpt library directory below
#SET(MRPT_DIR "/home/muhammad/Desktop/MRPT/mrpt-1.3.2/")
find_package(Qt5Widgets REQUIRED)
FIND_PACKAGE(MRPT REQUIRED vision;gui)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL)


# Tell CMake to create the helloworld executable
include_directories("headers")
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(test
  src/main.cpp
  src/GL_Widget.cpp
  headers/GL_Widget.h
)

qt5_use_modules(test Widgets OpenGL)
# Use the Widgets module from Qt 5.
target_link_libraries(test Qt5::Widgets)
TARGET_LINK_LIBRARIES(test ${MRPT_LIBS})
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

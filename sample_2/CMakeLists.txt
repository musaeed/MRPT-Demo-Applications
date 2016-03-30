cmake_minimum_required(VERSION 2.8.11)

project(mrpt_gridmap)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11 ON)
set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
# Find the MRPT directory, please change this to your library path
#SET(MRPT_DIR "/home/muhammad/Desktop/MRPT/mrpt-1.3.2/")
find_package(Qt5Widgets REQUIRED)
FIND_PACKAGE(MRPT REQUIRED vision;gui;maps)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL)


# Tell CMake to create the helloworld executable
include_directories("headers")
include_directories("ui")
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


set(HDRS
 headers/MainWindow.hpp
  headers/QtGL.hpp
headers/HelpDialog.hpp
headers/PropertyEditor.hpp
)

set(SRCS
	src/main.cpp
	src/QtGL.cpp
  	src/MainWindow.cpp
        src/HelpDialog.cpp
        src/PropertyEditor.cpp
)

set(UISS
   ui/MainWindow.ui
   ui/helpdialog.ui
   ui/propertyeditor.ui
)

set(RSCSS
  ui/resources.qrc
)

QT5_WRAP_UI(UIS ${UISS})
QT5_ADD_RESOURCES(RSCS ${RSCSS})
QT5_WRAP_CPP(MOCS ${SRCS})

add_executable(test ${UIS} ${RSCS} ${HDRS} ${SRCS})

qt5_use_modules(test Widgets OpenGL)
# Use the Widgets module from Qt 5.
target_link_libraries(test Qt5::Widgets)
TARGET_LINK_LIBRARIES(test ${MRPT_LIBS})
target_link_libraries(test ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

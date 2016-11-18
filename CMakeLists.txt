cmake_minimum_required(VERSION 3.6)
# Project Name
PROJECT(OpenGLCoursework)

#########################################################
# FIND GLUT
#########################################################
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# Include Files
#########################################################

set(SOURCE_FILES
        OpenGLCoursework.cpp
        objloader.hpp Cube.cpp Cube.h ShaderLoader.h PointLight.cpp PointLight.h Object.cpp Object.h Mesh.cpp Mesh.h Scene.cpp Scene.h ObjectInstance.cpp ObjectInstance.h Material.cpp Material.h Camera.cpp Camera.h)

add_executable(OpenGLCoursework ${SOURCE_FILES})

########################################################
# Linking & stuff
#########################################################

# create the program "OpenGLCoursework"
target_link_libraries(OpenGLCoursework ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
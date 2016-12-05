//
// Created by matt on 15/11/16.
//

#ifndef OPENGLCOURSEWORK_CUBE_H
#define OPENGLCOURSEWORK_CUBE_H

#include <vector>
#include <glm/vec3.hpp>
#include "Object.h"
#include "LoadTexture.h"

class Cube : public Object {
public:
    Cube();

    GLuint kanye = loadTexture("textures/kanye.bmp");
    GLuint steel = loadTexture("textures/steel.bmp");
    GLuint wood = loadTexture("textures/wood.bmp");
    GLuint water = loadTexture("textures/water.bmp");
    GLuint mud = loadTexture("textures/mud.bmp");
    GLuint brick = loadTexture("textures/brick.bmp");
};


#endif //OPENGLCOURSEWORK_CUBE_H

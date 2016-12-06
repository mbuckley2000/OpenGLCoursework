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

    GLuint kanye = loadBMP("textures/kanye.bmp");
    GLuint steel = loadBMP("textures/steel.bmp");
    GLuint wood = loadBMP("textures/wood.bmp");
    GLuint water = loadBMP("textures/water.bmp");
    GLuint mud = loadBMP("textures/mud.bmp");
    GLuint brick = loadBMP("textures/brick.bmp");
};


#endif //OPENGLCOURSEWORK_CUBE_H

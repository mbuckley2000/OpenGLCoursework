//
// Created by matt on 15/11/16.
//

#ifndef OPENGLCOURSEWORK_CUBE_H
#define OPENGLCOURSEWORK_CUBE_H

#include <vector>
#include <glm/vec3.hpp>
#include "Object.h"

class Cube : public Object {
public:
    Cube();
    void setSize(float size);
private:
    void updateVertices();
    float size;
    bool generated;
};


#endif //OPENGLCOURSEWORK_CUBE_H

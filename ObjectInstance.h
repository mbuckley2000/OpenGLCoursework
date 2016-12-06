//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_INSTANCE_H
#define OPENGLCOURSEWORK_INSTANCE_H


#include <glm/vec3.hpp>
#include "Object.h"

class ObjectInstance {
public:
    ObjectInstance(Object *object);

    GLuint texture;

    bool textureLoaded;

    glm::vec3 position;
    glm::vec3 angle;
    float scale;
    Object *object;

    bool visible;

    void center();

    void loadTexture(const char *filename);
};


#endif //OPENGLCOURSEWORK_INSTANCE_H

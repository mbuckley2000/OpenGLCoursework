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

    std::vector<GLuint> textures;

    bool textureLoaded;

    glm::vec3 position;
    glm::vec3 angle;

    int lastTex;

    float scale;
    Object *object;

    bool visible;

    char renderMode;

    void center();

    void loadTexture(const char *filename);
};


#endif //OPENGLCOURSEWORK_INSTANCE_H

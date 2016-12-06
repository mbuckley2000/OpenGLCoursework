//
// Created by matt on 18/11/16.
//

#include "ObjectInstance.h"
#include "LoadTexture.h"

ObjectInstance::ObjectInstance(Object *object) {
    this->object = object;
    scale = 1;
    position = {0, 0, 0};
    angle = {0, 0, 0};
    center();
    visible = true;
    textureLoaded = false;
}


void ObjectInstance::center() {
    //Mark Scheme: Bunny + screwdriver: 20% Correctly scaled and translated to fit inside the cube.
    glm::vec3 min = {0, 0, 0}, max = {0, 0, 0};
    for (glm::vec3 v : object->vertices) {
        if (v.x < min.x) min.x = v.x;
        if (v.y < min.y) min.y = v.y;
        if (v.z < min.z) min.z = v.z;
        if (v.x > max.x) max.x = v.x;
        if (v.y > max.y) max.y = v.y;
        if (v.z > max.z) max.z = v.z;
    }

    glm::vec3 size = max - min;
    float largestAxis = size.x;
    if (size.y > largestAxis) largestAxis = size.y;
    if (size.z > largestAxis) largestAxis = size.z;

    scale = 2 / largestAxis;

    position = -min * scale;
    position.x -= 1;
    position.y -= 1;
    position.z -= 1;
}

void ObjectInstance::loadTexture(const char *filename) {
    texture = loadBMP(filename);
    textureLoaded = true;
}

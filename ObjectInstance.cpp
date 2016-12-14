//
// Created by matt on 18/11/16.
//

#include <glm/glm.hpp>
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
    lastTex = 0;
    renderMode = 'f';
}


void ObjectInstance::center() {
    //Find minimum and maximum points of the object
    glm::vec3 min = {0, 0, 0}, max = {0, 0, 0};

    for (std::array<int, 3> face : object->faces) {
        for (int i = 0; i < face.size(); i++) {
            glm::vec3 v = object->vertices[i];
            if (v.x < min.x) min.x = v.x;
            if (v.y < min.y) min.y = v.y;
            if (v.z < min.z) min.z = v.z;
            if (v.x > max.x) max.x = v.x;
            if (v.y > max.y) max.y = v.y;
            if (v.z > max.z) max.z = v.z;
        }
    }

    //Calculate the vector length of the object
    glm::vec3 size = max - min;

    /*
    float largestAxis = size.x;
    if (size.y > largestAxis) largestAxis = size.y;
    if (size.z > largestAxis) largestAxis = size.z;
*/

    float length = std::sqrt(std::pow(size.x, 2) + std::pow(size.y, 2) + std::pow(size.z, 2));

    //Scale the instance to be 2x2x2
    scale = 2 / length;

    //Position the instance to be centered at (0, 0, 0)
    position = -min * scale;
    position.x -= 1;
    position.y -= 1;
    position.z -= 1;
}

void ObjectInstance::loadTexture(const char *filename) {
    textures.push_back(loadBMP(filename));
    textureLoaded = true;
}

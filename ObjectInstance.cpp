//
// Created by matt on 18/11/16.
//

#include <glm/glm.hpp>
#include <iostream>
#include "ObjectInstance.h"
#include "LoadTexture.h"

ObjectInstance::ObjectInstance(Object *object) {
    this->object = object;
    scale = 1;
    position = {0, 0, 0};
    angle = {0, 0, 0};
    visible = true;
    textureLoaded = false;
    lastTex = 0;
    renderMode = 'f';
}


void ObjectInstance::center() {
    //Find minimum and maximum points of the object
    glm::vec3 min = {0, 0, 0};
    glm::vec3 max = {0, 0, 0};

    for (std::array<int, 4> face : object->faces) {
        for (int i = 0; i < object->vn; i++) {
            glm::vec3 v = object->vertices[face[i]];
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

    float length = std::sqrt(std::pow(size.x, 2) + std::pow(size.y, 2) + std::pow(size.z, 2));

    std::cout << "Min: " << min.x << ", " << min.y << ", " << min.z << std::endl;
    std::cout << "Max: " << max.x << ", " << max.y << ", " << max.z << std::endl;
    std::cout << "Size: " << size.x << ", " << size.y << ", " << size.z << std::endl;

    //Scale the instance to be 2x2x2
    scale = 2 / length;

    //Position the instance to be centered at (0, 0, 0)
    position = -size;
    position /= 2;
    position -= min;
    position *= scale;
}

void ObjectInstance::loadTexture(const char *filename) {
    texture = loadBMP(filename);
    textureLoaded = true;
}

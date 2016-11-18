//
// Created by matt on 17/11/16.
//

#ifndef OPENGLCOURSEWORK_POINTLIGHT_H
#define OPENGLCOURSEWORK_POINTLIGHT_H


#include <glm/vec3.hpp>

class PointLight {
    public:
    PointLight();

    float intensity;
    glm::vec3 position;
    glm::vec3 colour;
};


#endif //OPENGLCOURSEWORK_POINTLIGHT_H

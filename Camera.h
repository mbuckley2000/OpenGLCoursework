//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_CAMERA_H
#define OPENGLCOURSEWORK_CAMERA_H


#include <glm/vec3.hpp>


class Camera {
public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 direction;
    glm::vec3 right;
};


#endif //OPENGLCOURSEWORK_CAMERA_H

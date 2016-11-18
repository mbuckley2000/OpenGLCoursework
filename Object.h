//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_OBJECT_H
#define OPENGLCOURSEWORK_OBJECT_H


#include <glm/vec3.hpp>
#include <vector>
#include <array>

class Object {
protected:
    double scale;
    std::vector<std::array<int, 3>> faces;
    std::vector<glm::vec3> vertices;
    glm::vec3 colour;
};


#endif //OPENGLCOURSEWORK_OBJECT_H

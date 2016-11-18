//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_OBJECT_H
#define OPENGLCOURSEWORK_OBJECT_H


#include <glm/vec3.hpp>
#include <vector>
#include <array>
#include "Material.h"

class Object {
public:
    double scale;
    std::vector<std::array<int, 3>> faces;
    std::vector<glm::vec3> vertices;
    Material material;
};


#endif //OPENGLCOURSEWORK_OBJECT_H

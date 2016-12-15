//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_OBJECT_H
#define OPENGLCOURSEWORK_OBJECT_H


#include <glm/vec3.hpp>
#include <vector>
#include <array>
#include <GL/gl.h>
#include "Material.h"

class Object {
public:
    double scale;
    std::vector<std::array<int, 4>> faces;
    std::vector<glm::vec3> vertices;
    Material material;
    std::vector<std::array<glm::vec2, 4>> uvs;
    std::vector<glm::vec3> vertexNormals;

    int vn;

    void calculateNormals();
};


#endif //OPENGLCOURSEWORK_OBJECT_H

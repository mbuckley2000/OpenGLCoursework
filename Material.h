//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_MATERIAL_H
#define OPENGLCOURSEWORK_MATERIAL_H


#include <glm/vec3.hpp>

class Material {
public:
    Material();

    glm::vec3 emissiveColour;
    float reflectivity;
};


#endif //OPENGLCOURSEWORK_MATERIAL_H

//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_MESH_H
#define OPENGLCOURSEWORK_MESH_H


#include "Object.h"

class Mesh : public Object {
public:
    void loadFromFile(const char* path);
};


#endif //OPENGLCOURSEWORK_MESH_H

//
// Created by matt on 18/11/16.
//

#include "Mesh.h"
#include "objloader.hpp"

void Mesh::loadFromFile(const char *path) {
    load_obj(path, vertices, faces);
}

Mesh::Mesh(const char *path) {
    loadFromFile(path);
    calculateNormals();
}

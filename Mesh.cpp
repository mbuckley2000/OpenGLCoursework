//
// Created by matt on 18/11/16.
//

#include "Mesh.h"
#include "objloader.hpp"

void Mesh::loadFromFile(const char *path) {
    load_obj(path, vertices, faces);
}

Mesh::Mesh(const char *path) {
    vn = 3;
    loadFromFile(path);
    calculateNormals();

}

void Mesh::flip() {
    for (glm::vec3 v : vertices) {
        v = -v;
    }

    calculateNormals();
}

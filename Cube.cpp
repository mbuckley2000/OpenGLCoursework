//
// Created by matt on 15/11/16.
//

#include <glm/vec2.hpp>
#include "Cube.h"

Cube::Cube() {
    for (int i = 0; i < 8; i++) {
        glm::vec3 v;
        glm::vec2 uv;
        vertices.push_back(v);
        uvs.push_back(uv);
    }
    for (int i = 0; i < 12; i++) {
        std::array<int, 3> a;
        faces.push_back(a);
    }

    faces[0] = {0, 1, 2};
    faces[1] = {1, 2, 3};
    faces[2] = {2, 3, 6};
    faces[3] = {3, 6, 7};
    faces[4] = {6, 7, 4};
    faces[5] = {7, 4, 5};
    faces[6] = {4, 5, 1};
    faces[7] = {4, 1, 0};
    faces[8] = {5, 1, 3};
    faces[9] = {5, 3, 7};
    faces[10] = {2, 0, 4};
    faces[11] = {2, 6, 4};

    vertices[0] = {1, 1, 1};
    vertices[1] = {-1, 1, 1};
    vertices[2] = {1, -1, 1};
    vertices[3] = {-1, -1, 1};
    vertices[4] = {1, 1, -1};
    vertices[5] = {-1, 1, -1};
    vertices[6] = {1, -1, -1};
    vertices[7] = {-1, -1, -1};

    uvs[0] = {1, 1};
    uvs[1] = {0, 1};
    uvs[2] = {1, 0};
    uvs[3] = {1, 1};
    uvs[4] = {0, 1};
    uvs[5] = {1, 0};
    uvs[6] = {1, 1};
    uvs[7] = {0, 1};


    glGenTextures(1, &kanye);
    glGenTextures(1, &steel);
    glGenTextures(1, &wood);
    glGenTextures(1, &brick);
    glGenTextures(1, &water);
    glGenTextures(1, &mud);
}
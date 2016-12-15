//
// Created by matt on 15/11/16.
//

#include <glm/vec2.hpp>
#include "Cube.h"

Cube::Cube() {
    vn = 4;

    for (int i = 0; i < 8; i++) {
        glm::vec3 v;
        std::array<glm::vec2, 4> uv;
        vertices.push_back(v);
        uvs.push_back(uv);
    }
    for (int i = 0; i < 6; i++) {
        std::array<int, 4> a;
        faces.push_back(a);
    }

    faces[0] = {4, 0, 2, 6}; //Front
    uvs[0][0] = {0.25, 2 / 3};
    uvs[0][1] = {0.5, 2 / 3};
    uvs[0][2] = {0.5, 1 / 3};
    uvs[0][3] = {0.25, 1 / 3};
    faces[1] = {1, 5, 7, 3}; //Back
    uvs[1][0] = {0.75, 2 / 3};
    uvs[1][1] = {1, 2 / 3};
    uvs[1][2] = {1, 1 / 3};
    uvs[1][3] = {0.75, 1 / 3};
    faces[2] = {5, 4, 6, 7}; //Left
    uvs[2][0] = {0, 2 / 3};
    uvs[2][1] = {0.25, 2 / 3};
    uvs[2][2] = {0.25, 1 / 3};
    uvs[2][3] = {0, 1 / 3};
    faces[3] = {0, 1, 3, 2}; //Right
    uvs[3][0] = {0.5, 2 / 3};
    uvs[3][1] = {0.75, 2 / 3};
    uvs[3][2] = {0.75, 1 / 3};
    uvs[3][3] = {0.5, 1 / 3};
    faces[4] = {5, 1, 0, 4}; //Top
    uvs[4][0] = {0.25, 1};
    uvs[4][1] = {0.5, 1};
    uvs[4][2] = {0.5, 2 / 3};
    uvs[4][3] = {0.25, 2 / 3};
    faces[5] = {6, 2, 3, 7}; //Bottom
    uvs[5][0] = {0.25, 1 / 3};
    uvs[5][1] = {0.5, 1 / 3};
    uvs[5][2] = {0.5, 0};
    uvs[5][3] = {0.25, 0};

    vertices[4] = {1, 1, -1};   //Front Top Left
    vertices[0] = {1, 1, 1};    //Front Top Right
    vertices[6] = {1, -1, -1};  //Front Bottom Left
    vertices[2] = {1, -1, 1};   //Front Bottom Right
    vertices[5] = {-1, 1, -1}; //Back Top Left
    vertices[1] = {-1, 1, 1}; //Back Top Right
    vertices[7] = {-1, -1, -1}; //Back Bottom Left
    vertices[3] = {-1, -1, 1}; //Back Bottom Right
    calculateNormals();
}
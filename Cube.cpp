//
// Created by matt on 15/11/16.
//

#include "Cube.h"

Cube::Cube() {
    size = 2;
    generated = false;
    updateVertices();
}

void Cube::updateVertices() {
    if (!generated) {
        for (int i = 0; i < 8; i++) {
            glm::vec3 v;
            vertices.push_back(v);
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
    }

    vertices[0] = {size/2, size/2, size/2};
    vertices[1] = {-size/2, size/2, size/2};
    vertices[2] = {size/2, -size/2, size/2};
    vertices[3] = {-size/2, -size/2, size/2};
    vertices[4] = {size/2, size/2, -size/2};
    vertices[5] = {-size/2, size/2, -size/2};
    vertices[6] = {size/2, -size/2, -size/2};
    vertices[7] = {-size/2, -size/2, -size/2};
}


/*

  //Face 1 + opposite
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

            glVertex3f(1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);

            //Face 2 + opposite
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);

            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);

            //Face 3 + opposite
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, 1.0f);
            glVertex3f(-1.0f, 1.0f, -1.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);

            glVertex3f(1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, 1.0f);
            glVertex3f(-1.0f, -1.0f, -1.0f);
            glVertex3f(1.0f, -1.0f, -1.0f);


 */


void Cube::setSize(float size) {
    this->size = size;
    updateVertices();
}
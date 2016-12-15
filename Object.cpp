//
// Created by matt on 18/11/16.
//

#include <glm/glm.hpp>
#include "Object.h"

void Object::calculateNormals() {
    //Iterate through each vertex
    for (int i = 0; i < vertices.size(); i++) {
        glm::vec3 vertNormal = {0, 0, 0};
        int faceCount = 0;

        //Find all faces which contain this vertex
        for (std::array<int, 4> face : faces) {
            bool hit = false;
            for (int j = 0; j < vn; j++) {
                if (face[j] == i) hit = true;
            }
            if (hit) {
                //Calculate face normal
                vertNormal += glm::normalize(
                        glm::cross(vertices[face[1]] - vertices[face[0]], vertices[face[2]] - vertices[face[0]]));

                faceCount++; //Add to vertex normal
            }
        }

        vertNormal /= faceCount; //Divide by number of faces found to get average normal

        vertexNormals.push_back(vertNormal);
    }
}
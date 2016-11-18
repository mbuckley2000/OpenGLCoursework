//
// Created by matt on 18/11/16.
//

#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <iostream>
#include "Scene.h"

void Scene::drawTriangle(std::array<glm::vec3, 3> vertices, glm::vec3 colour) {
    std::cout << "Drawing triangle" << std::endl;
    //Calculate face position
    glm::vec3 facePos;
    for (glm::vec3 v : vertices) {
        facePos += v;
    }
    facePos /= 3;

    glm::vec3 faceNorm = glm::normalize(glm::cross(vertices[2] - vertices[0], vertices[2] - vertices[1]));

    //Diffuse
    glm::vec3 aoi = light->position - facePos;
    float diffuseBrightness = light->intensity * glm::dot(faceNorm, glm::normalize(aoi)) / pow(glm::length(aoi), 2);

    //Specular
    //http://learnopengl.com/#!Lighting/Basic-Lighting

    //Emmissive
    float emmissiveBrightness = 0.05;

    //Calculate face colour
    float brightness = diffuseBrightness + emmissiveBrightness;
    if (brightness > 1) brightness = 1;
    colour *= light->colour;
    glColor3f(colour.r * brightness, colour.g * brightness, colour.b * brightness);

    //Draw face
    for (glm::vec3 v : vertices) {
        glVertex3f(v.x, v.y, v.z);
    }
}

void Scene::drawInstance(ObjectInstance *instance) {
    glBegin(GL_TRIANGLES);
    //std::cout << "Displaying object" << std::endl;
    //Iterate over faces
    for (std::array<int, 3> face : instance->object->faces) {
        //iterate over vertices
        drawTriangle({instance->object->vertices[face[0]] * instance->scale,
                      instance->object->vertices[face[1]] * instance->scale,
                      instance->object->vertices[face[2]] * instance->scale},
                     instance->object->material.emissiveColour);
    }
    glEnd();
}

void Scene::render() {
    gluLookAt(camera->position.x, camera->position.y, camera->position.z,
              camera->center.x, camera->center.y, camera->center.z,
              camera->up.x, camera->up.y, camera->up.z);

    for (ObjectInstance *instance : objectInstances) {
        drawInstance(instance);
    }
}
//
// Created by matt on 18/11/16.
//

#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <iostream>
#include "Scene.h"

void Scene::drawTriangle(std::array<glm::vec3, 3> vertices, glm::vec3 colour) {
    //Calculate face position
    glm::vec3 facePos;
    for (glm::vec3 v : vertices) {
        facePos += v;
    }
    facePos /= 3;

    glm::vec3 faceNorm = glm::normalize(glm::cross(vertices[2] - vertices[0], vertices[2] - vertices[1]));

    //glNormal3f(faceNorm.x, faceNorm.y, faceNorm.z); //GL lighting

    colour *= light->colour;

    //Draw face + calculate lighting per vertex
    for (glm::vec3 v : vertices) {

        //Diffuse
        glm::vec3 aoi = light->position - v;

        float diffuseBrightness = light->intensity * glm::dot(faceNorm, glm::normalize(aoi)) / pow(glm::length(aoi), 2);
        if (diffuseBrightness < 0) diffuseBrightness = 0;

        //Specular
        //http://learnopengl.com/#!Lighting/Basic-Lighting
        //glm::vec3 aoiCam = camera->position - v;

        //float spec = 100 / (0.0001 + pow(glm::length(glm::dot(aoi, aoiCam)), 2) * (pow(glm::length(aoi), 2) + pow(glm::length(aoiCam),2))); //TODO Take reflectivity into account
        //if (spec < 0) spec = 0;

        //Emmissive
        float emmissiveBrightness = 0.05;

        //Calculate face colour
        float brightness = diffuseBrightness + emmissiveBrightness;
        if (brightness > 1) brightness = 1;
        glColor3f(colour.r * brightness, colour.g * brightness, colour.b * brightness);
        glVertex3f(v.x, v.y, v.z);
    }
}

void Scene::drawInstance(ObjectInstance *instance) {
    if (renderMode == 'e') glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (renderMode == 'v') {
        glBegin(GL_POINTS);
    } else {
        glBegin(GL_TRIANGLES);
    }

    //glColor3f(instance->object->material.emissiveColour.x, instance->object->material.emissiveColour.y, instance->object->material.emissiveColour.z); //For gl lighting

    //Iterate over faces
    for (std::array<int, 3> face : instance->object->faces) {
        //iterate over vertices
        drawTriangle({instance->object->vertices[face[0]] * instance->scale + instance->position,
                      instance->object->vertices[face[1]] * instance->scale + instance->position,
                      instance->object->vertices[face[2]] * instance->scale + instance->position},
                     instance->object->material.emissiveColour);
    }
    glEnd();
}

void Scene::render() {
    //gluLookAt(camera->position.x, camera->position.y, camera->position.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
    glm::vec3 lookAt = camera->position + camera->direction;
    gluLookAt(camera->position.x, camera->position.y, camera->position.z, lookAt.x, lookAt.y, lookAt.z, camera->up.x,
              camera->up.y, camera->up.z);

    for (ObjectInstance *instance : objectInstances) {
        drawInstance(instance);
    }
}

Scene::Scene() {
    renderMode = 'f';
}

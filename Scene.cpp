//
// Created by matt on 18/11/16.
//

#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <iostream>
#include "Scene.h"

void Scene::drawTriangle(int v1, int v2, int v3, ObjectInstance *instance) {
    //Calculate face position
    glm::vec3 facePos;
    facePos = instance->object->vertices[v1] + instance->object->vertices[v2] + instance->object->vertices[v3];
    facePos /= 3;

    glm::vec3 faceNorm = glm::normalize(glm::cross(instance->object->vertices[v3] - instance->object->vertices[v1],
                                                   instance->object->vertices[v3] - instance->object->vertices[v2]));

    glNormal3f(faceNorm.x, faceNorm.y, faceNorm.z); //GL lighting


    if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v1].x, instance->object->uvs[v1].y);
    glVertex3f(instance->object->vertices[v1].x, instance->object->vertices[v1].y, instance->object->vertices[v1].z);
    if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v2].x, instance->object->uvs[v2].y);
    glVertex3f(instance->object->vertices[v2].x, instance->object->vertices[v2].y, instance->object->vertices[v2].z);
    if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v3].x, instance->object->uvs[v3].y);
    glVertex3f(instance->object->vertices[v3].x, instance->object->vertices[v3].y, instance->object->vertices[v3].z);

    //colour *= light->colour;

    //Draw face + calculate lighting per vertex
    //for (glm::vec3 v : vertices) {
/*
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
        */
}


void Scene::drawInstance(ObjectInstance *instance) {
    if (renderMode == 'e') glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (renderMode == 'v') {
        glBegin(GL_POINTS);
    } else {
        glBegin(GL_TRIANGLES);
    }

    //glColor3f(instance->object->material.emissiveColour.x, instance->object->material.emissiveColour.y, instance->object->material.emissiveColour.z); //For gl lighting
    glBindTexture(GL_TEXTURE_2D, instance->texture);

    //Iterate over faces
    for (std::array<int, 3> face : instance->object->faces) {
        //iterate over vertices
        drawTriangle(face[0], face[1], face[2], instance);
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

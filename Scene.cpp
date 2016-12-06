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

    float scale = instance->scale;
    glm::vec3 pos = instance->position;

    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v1].x, instance->object->uvs[v1].y);
    glVertex3f(instance->object->vertices[v1].x * scale + pos.x, instance->object->vertices[v1].y * scale + pos.y,
               instance->object->vertices[v1].z * scale + pos.z);
    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v2].x, instance->object->uvs[v2].y);
    glVertex3f(instance->object->vertices[v2].x * scale + pos.x, instance->object->vertices[v2].y * scale + pos.y,
               instance->object->vertices[v2].z * scale + pos.z);
    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v3].x, instance->object->uvs[v3].y);
    glVertex3f(instance->object->vertices[v3].x * scale + pos.x, instance->object->vertices[v3].y * scale + pos.y,
               instance->object->vertices[v3].z * scale + pos.z);

}


void Scene::drawInstance(ObjectInstance *instance) {
    if (renderMode == 'e') glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (renderMode == 'v') {
        glBegin(GL_POINTS);
    } else {
        glBegin(GL_TRIANGLES);
    }

    if (instance->textureLoaded) {
        glBindTexture(GL_TEXTURE_2D, instance->texture);
    } else {
        glColor3f(1, 1, 1);
    }

    //Iterate over faces
    for (std::array<int, 3> face : instance->object->faces) {
        //iterate over vertices
        drawTriangle(face[0], face[1], face[2], instance);
    }
    glEnd();

    if (renderMode == 'v') glPointSize(5);
}

void Scene::render() {
    //GL Light
    GLfloat pos[] = {light->position.x, light->position.y, light->position.z, 1};
    GLfloat color[] = {light->colour.r, light->colour.g, light->colour.b, 1};
    GLfloat cutoff[] = {100};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);

    glm::vec3 lookAt = camera->position + camera->direction;
    gluLookAt(camera->position.x, camera->position.y, camera->position.z, lookAt.x, lookAt.y, lookAt.z, camera->up.x,
              camera->up.y, camera->up.z);

    for (ObjectInstance *instance : objectInstances) {
        if (instance->visible) drawInstance(instance);
    }
}

Scene::Scene() {
    renderMode = 'f';
}

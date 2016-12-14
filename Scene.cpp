//
// Created by matt on 18/11/16.
//

#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <iostream>
#include "Scene.h"

void Scene::drawTriangle(int v1, int v2, int v3, ObjectInstance *instance) {
    float scale = instance->scale;
    glm::vec3 pos = instance->position;

    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v1].x, instance->object->uvs[v1].y);
    glNormal3f(instance->object->vertexNormals[v1].x, instance->object->vertexNormals[v1].y,
               instance->object->vertexNormals[v1].z); //GL lighting
    glVertex3f(instance->object->vertices[v1].x * scale + pos.x, instance->object->vertices[v1].y * scale + pos.y,
               instance->object->vertices[v1].z * scale + pos.z);

    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v2].x, instance->object->uvs[v2].y);
    glNormal3f(instance->object->vertexNormals[v2].x, instance->object->vertexNormals[v2].y,
               instance->object->vertexNormals[v2].z); //GL lighting
    glVertex3f(instance->object->vertices[v2].x * scale + pos.x, instance->object->vertices[v2].y * scale + pos.y,
               instance->object->vertices[v2].z * scale + pos.z);


    if (instance->textureLoaded)
        if (instance->object->uvs.size() == instance->object->vertices.size())
        glTexCoord2f(instance->object->uvs[v3].x, instance->object->uvs[v3].y);
    glNormal3f(instance->object->vertexNormals[v3].x, instance->object->vertexNormals[v3].y,
               instance->object->vertexNormals[v3].z); //GL lighting
    glVertex3f(instance->object->vertices[v3].x * scale + pos.x, instance->object->vertices[v3].y * scale + pos.y,
               instance->object->vertices[v3].z * scale + pos.z);

}


void Scene::drawInstance(ObjectInstance *instance) {
    //Draw Axes
    glBegin(GL_LINES);

    glVertex3f(-20, 0, 0); //X
    glVertex3f(20, 0, 0);

    glVertex3f(0, -20, 0); //Y
    glVertex3f(0, 20, 0);

    glVertex3f(0, 0, -20); //Z
    glVertex3f(0, 0, 20);

    glEnd();

    glPushMatrix();
    glRotatef(instance->angle.x, 1, 0, 0);
    glRotatef(instance->angle.y, 0, 1, 0);
    glRotatef(instance->angle.z, 0, 0, 1);


    if (instance->renderMode == 'e') glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (instance->renderMode == 'v') {
        glBegin(GL_POINTS);
    } else {
        glBegin(GL_TRIANGLES);
    }

    if (instance->textureLoaded) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, instance->textures[0]);
    } else {
        glColor3f(1, 1, 1);
    }

    //Iterate over faces
    for (std::array<int, 3> face : instance->object->faces) {
        drawTriangle(face[0], face[1], face[2], instance);
    }
    glEnd();
    glPopMatrix();

    glPointSize(3);
    glLineWidth(3);
}

void Scene::render() {
    //Update light
    GLfloat pos[] = {light->position.x, light->position.y, light->position.z, 1};
    GLfloat color[] = {light->colour.r, light->colour.g, light->colour.b, 1};
    GLfloat cutoff[] = {100};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);

    //Update camera
    glm::vec3 lookAt = camera->position + camera->direction;
    gluLookAt(camera->position.x, camera->position.y, camera->position.z, lookAt.x, lookAt.y, lookAt.z, camera->up.x,
              camera->up.y, camera->up.z);

    //Draw all object instances
    for (ObjectInstance *instance : objectInstances) {
        if (instance->visible) drawInstance(instance);
    }
}
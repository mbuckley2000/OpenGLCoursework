//
// Created by matt on 18/11/16.
//

#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <GL/glu.h>
#include <iostream>
#include "Scene.h"

//Special workaround cube because I couldn't get uv mapping with quads isn't 100% in my rendering engine.
//This is called whenever an instance's object uses quad faces.
void Scene::drawCube(ObjectInstance *instance) {
    //Front
    glNormal3f(0, 0, 1);
    if (instance->textureLoaded) glTexCoord2f(0, 0.5);
    glVertex3f(-1, -1, 1);
    if (instance->textureLoaded) glTexCoord2f(0.25, 0.5);
    glVertex3f(1, -1, 1);
    if (instance->textureLoaded) glTexCoord2f(0.25, 0.25);
    glVertex3f(1, 1, 1);
    if (instance->textureLoaded) glTexCoord2f(0, 0.25);
    glVertex3f(-1, 1, 1);

    //Back
    glNormal3f(0, 0, -1);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.5);
    glVertex3f(-1, -1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.5, 0.5);
    glVertex3f(1, -1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.5, 0.25);
    glVertex3f(1, 1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.25);
    glVertex3f(-1, 1, -1);

    //Top
    glNormal3f(0, 1, 0);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.25);
    glVertex3f(-1, 1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.5);
    glVertex3f(-1, 1, 1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.5);
    glVertex3f(1, 1, 1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.25);
    glVertex3f(1, 1, -1);

    //Bot
    glNormal3f(0, -1, 0);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.5);
    glVertex3f(-1, -1, -1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.5);
    glVertex3f(-1, -1, 1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.75);
    glVertex3f(1, -1, 1);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.75);
    glVertex3f(1, -1, -1);

    //Left
    glNormal3f(-1, 0, 0);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.5);
    glVertex3f(-1, -1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.75, 0.25);
    glVertex3f(-1, 1, -1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.25);
    glVertex3f(-1, 1, 1);
    if (instance->textureLoaded) glTexCoord2f(1, 0.5);
    glVertex3f(-1, -1, 1);

    //Right
    glNormal3f(1, 0, 0);
    if (instance->textureLoaded) glTexCoord2f(0.5, 0.5);
    glVertex3f(1, -1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.5, 0.25);
    glVertex3f(1, 1, -1);
    if (instance->textureLoaded) glTexCoord2f(0.25, 0.25);
    glVertex3f(1, 1, 1);
    if (instance->textureLoaded) glTexCoord2f(0.25, 0.5);
    glVertex3f(1, -1, 1);
}

void Scene::drawInstance(ObjectInstance *instance) {
    float scale = instance->scale;
    glm::vec3 pos = instance->position;

    //Iterate over faces
    for (int fn = 0; fn < instance->object->faces.size(); fn++) {
        for (int i = 0; i < instance->object->vn; i++) {
            int vi = instance->object->faces[fn][i];
            glm::vec3 v = instance->object->vertices[vi];

            if (instance->textureLoaded) {
                //if (instance->object->uvs.size() == instance->object->faces.size()) {
                glTexCoord2f(instance->object->uvs[fn][i].x, instance->object->uvs[fn][i].y);
                //}
            }
            glNormal3f(instance->object->vertexNormals[vi].x, instance->object->vertexNormals[vi].y,
                       instance->object->vertexNormals[vi].z); //GL lighting
            glVertex3f(v.x * scale + pos.x, v.y * scale + pos.y, v.z * scale + pos.z);
        }
    }
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

    //Draw Axes
    glBegin(GL_LINES);

    glVertex3f(-20, 0, 0); //X
    glVertex3f(20, 0, 0);

    glVertex3f(0, -20, 0); //Y
    glVertex3f(0, 20, 0);

    glVertex3f(0, 0, -20); //Z
    glVertex3f(0, 0, 20);

    glEnd();


    //Draw all object instances
    for (ObjectInstance *instance : objectInstances) {
        if (instance->visible) {
            //Push matrix for rotation
            glPushMatrix();

            //Rotate the object in X, Y, Z order.
            //This is reversed, because OpenGL applied rotations in reverse
            glRotatef(instance->angle.z, 0, 0, 1);
            glRotatef(instance->angle.y, 0, 1, 0);
            glRotatef(instance->angle.x, 1, 0, 0);

            //Set render mode (Edge, Vertex, Face)
            if (instance->renderMode == 'e') glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            if (instance->renderMode == 'v') {
                glBegin(GL_POINTS);
            } else {
                if (instance->object->vn == 4) {
                    glBegin(GL_QUADS); //For objects with quad faces
                } else {
                    glBegin(GL_TRIANGLES); //For objects with triangle faces
                }
            }

            //Set texture / colour
            if (instance->textureLoaded) {
                glBindTexture(GL_TEXTURE_2D, instance->texture);
            } else {
                glColor3f(1, 1, 1);
            }

            //Draw the instance
            if (instance->object->vn == 4) {
                drawCube(instance); //Special case for cube. Workaround for UV mapping on quads.
            } else {
                drawInstance(instance);
            }

            //End drawing and pop the matrix for rotation
            glEnd();
            glPopMatrix();
        }
    }

    glPointSize(3);
    glLineWidth(3);
}
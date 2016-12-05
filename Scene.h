//
// Created by matt on 18/11/16.
//

#ifndef OPENGLCOURSEWORK_SCENE_H
#define OPENGLCOURSEWORK_SCENE_H


#include "ObjectInstance.h"
#include "PointLight.h"
#include "Camera.h"

class Scene {
public:
    void render();

    Scene();
    std::vector<ObjectInstance *> objectInstances;
    PointLight *light;
    Camera *camera;

    char renderMode;

private:
    void drawTriangle(int v1, int v2, int v3, ObjectInstance *instance);

    void drawInstance(ObjectInstance *instance);
};


#endif //OPENGLCOURSEWORK_SCENE_H

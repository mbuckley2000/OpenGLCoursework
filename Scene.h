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

    std::vector<ObjectInstance *> objectInstances;
    PointLight *light;
    Camera *camera;

private:
    void drawCube(ObjectInstance *instance);
    void drawInstance(ObjectInstance *instance);
};


#endif //OPENGLCOURSEWORK_SCENE_H

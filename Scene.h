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
    void drawTriangle(std::array<glm::vec3, 3> vertices, glm::vec3 colour);

    void drawInstance(ObjectInstance *instance);
};


#endif //OPENGLCOURSEWORK_SCENE_H

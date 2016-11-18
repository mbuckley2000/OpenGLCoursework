//
// Created by matt on 18/11/16.
//

#include "ObjectInstance.h"

ObjectInstance::ObjectInstance(Object *object) {
    this->object = object;
    scale = 1;
    position = {0, 0, 0};
    angle = {0, 0, 0};
}
//
// Created by matt on 15/11/16.
//

#ifndef OPENGLCOURSEWORK_CUBE_H
#define OPENGLCOURSEWORK_CUBE_H

#include <vector>
#include "Vertex.h"

class Cube {
public:
    Cube(double xPos, double yPos, double zPos, double size);


private:
    std::vector<float> position;
    std::vector<float> angle;
    double size;
};


#endif //OPENGLCOURSEWORK_CUBE_H

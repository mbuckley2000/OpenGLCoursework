//
// Created by matt on 15/11/16.
//

#include "Vertex.h"

Vertex::Vertex(double x, double y, double z) {
    setX(x);
    setY(y);
    setZ(z);
}

double Vertex::getX() const {
    return x;
}

void Vertex::setX(double x) {
    Vertex::x = x;
}

double Vertex::getY() const {
    return y;
}

void Vertex::setY(double y) {
    Vertex::y = y;
}

double Vertex::getZ() const {
    return z;
}

void Vertex::setZ(double z) {
    Vertex::z = z;
}

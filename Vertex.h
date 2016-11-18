//
// Created by matt on 15/11/16.
//

#ifndef OPENGLCOURSEWORK_VERTEX_H
#define OPENGLCOURSEWORK_VERTEX_H


class Vertex {
public:
    Vertex(double x, double y, double z);

    double getX() const;

    void setX(double x);

    double getY() const;

    void setY(double y);

    double getZ() const;

    void setZ(double z);

private:
    double x, y, z;
};


#endif //OPENGLCOURSEWORK_VERTEX_H

#ifndef CUBE_H
#define CUBE_H

#include "cuboid.h"
#include <iostream>

/*
Derived class for a cube, implemented as specialisation of cuboid class
*/

class Cube : public Cuboid
{
public:
    Cube();
    Cube(const double&);
    ~Cube(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif
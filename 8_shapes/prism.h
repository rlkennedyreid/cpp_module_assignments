#ifndef PRISM_H
#define PRISM_H

#include "shape.h"
#include <iostream>

/*
Derived class for a prism
- Member data is double depth_ and a base Shape, which projects to 3D with depth_
*/
class Prism : public Shape
{
private:
    double depth_;
    Shape* base_;
public:
    Prism();
    Prism(const double&, Shape*);
    ~Prism(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif
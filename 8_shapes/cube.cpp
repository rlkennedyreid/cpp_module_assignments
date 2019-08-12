#include "cube.h"

// Printing messages in constructors for demonstration
Cube::Cube() : Cuboid() {
    std::cout << "Cube: Default constructor called" << std::endl;
}

Cube::Cube(const double& length) : Cuboid(length, length, length) {
    std::cout << "Cube: Parameterised constructor called" << std::endl;
}

double Cube::GetArea() const{
    return 2.0 * (height_*width_ + height_*depth_ + width_*depth_);
}

double Cube::GetVolume() const{
    return height_*width_*depth_;
}

std::string Cube::PrintType() const{
    return "Cube";
}
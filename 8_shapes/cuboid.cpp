#include "cuboid.h"

// Printing messages in constructors for demonstration
Cuboid::Cuboid() : height_(.0), width_(.0) {
    std::cout << "Cuboid: Default constructor called" << std::endl;
}

Cuboid::Cuboid(const double& height, const double& width, const double& depth) 
    : height_(height), width_(width), depth_(depth) {
    std::cout << "Cuboid: Parameterised constructor called" << std::endl;
}

double Cuboid::GetArea() const{
    return 2.0 * (height_*width_ + height_*depth_ + width_*depth_);
}

double Cuboid::GetVolume() const{
    return height_*width_*depth_;
}

std::string Cuboid::PrintType() const{
    return "Cuboid";
}